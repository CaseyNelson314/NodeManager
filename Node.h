/**
        @file   Node.h
        @brief  シーケンス制御を行うクラス
        @author CaseyNelson
        @date   2022/05/07
*/

#pragma once

class Node {

    Node *next;
    Node *prev;

    void (*user_begin)(void) = nullptr; //移行した直後に呼ばれる
    void (*user_main)(void)  = nullptr; //移行するまで呼び続けられる
    void (*user_end)(void)   = nullptr; //移行する直前に呼ばれる

    bool isThisScene = false; //自身の番であるか
    bool onBeginLoop = true;
    bool onSetupLoop = true;

  public:

    Node(Node &next, Node &prev):
      next(&next), prev(&prev) {};

    void connectNext(Node &next) {
      this->next = &next;
    }
    void connectPrev(Node &prev) {
      this->prev = &prev;
    }

    //自身のインスタンスからシーンを開始
    void begin() {
      if (user_begin)user_begin();
      isThisScene = true;
      onBeginLoop = true;
    }
    //自身のインスタンスのシーンの場合user_main関数を呼ぶ
    void update() {
      if (isThisScene) {
        if (user_main)user_main();
        onBeginLoop = false;
        onSetupLoop = false;
      }
    }
    //自身のインスタンスのシーンを終了
    void end() {
      if (user_end)user_end();
      isThisScene = false;
    }

    //シーン移行時のコールバック関数設定
    void setBegin(void (*callback)(void)) {
      user_begin = callback;
    }
    void setMain(void (*callback)(void)) {
      user_main = callback;
    }
    void setEnd(void (*callback)(void)) {
      user_end = callback;
    }

    //user_mainが呼ばれる時一度だけtrueを返す
    bool onBegin() const {
      return onBeginLoop;
    }
    //Setup後のループの時だけtrueを返す
    bool onSetup() const {
      return onSetupLoop;
    }
    //自分のシーンであるか
    bool isEnable() const {
      return isThisScene;
    }

    //次のシーンに移行する
    void changeNext() {
      end();
      next->begin();
    }
    //前のシーンに移行する
    void changePrev() {
      end();
      prev->begin();
    }

};
