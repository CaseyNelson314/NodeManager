/**
        @file   SequenceManager.h
        @brief  シーケンス制御を行うクラス
        @author CaseyNelson
        @date   2022/05/07
*/

#pragma once

class SequenceManager {

    SequenceManager *nextScene; //次のシーンのインスタンスポインタ
    SequenceManager *prevScene; //前のシーンのインスタンスポインタ

    void (*user_begin)(void) = nullptr; //移行した直後に呼ばれる
    void (*user_main)(void) = nullptr;  //移行するまで呼び続けられる
    void (*user_end)(void) = nullptr;   //移行する直前に呼ばれる

    bool isMyScene = false; //自身の番であるか
    uint32_t startTime;     //シーンが開始された時刻

  public:

    //次のシーンのインスタンスポインタ、前のシーンのインスタンスポインタ
    //前のシーンに戻る必要がない場合、引数*prevSceneを空にする
    SequenceManager(SequenceManager *nextScene, SequenceManager *prevScene = nullptr):
      nextScene(nextScene), prevScene(prevScene) {};
    SequenceManager(void) {};

    void setnextScene(SequenceManager *nextScene) {
      this->nextScene = nextScene;
    }
    void setprevScene(SequenceManager *prevScene) {
      this->prevScene = prevScene;
    }

    //自身のインスタンスからシーケンス処理を開始
    void begin() {
      if (user_begin != nullptr)user_begin();
      isMyScene = true;
      startTime = millis();
    }

    //自分のシーンの場合user_main関数を呼ぶ
    void update() {
      if (isMyScene && user_main != nullptr)user_main();
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

    //指定時間経過後、次のシーンに移行する
    void updateTimer(uint32_t timeMs) {
      if (millis() - startTime > timeMs && isMyScene)
        changeNext();
    }

    //次のシーンに移行する
    void changeNext() {
      if (user_end != nullptr)user_end();
      isMyScene = false;
      nextScene->begin();
    }
    //前のシーンに移行する
    void changePrev() {
      if (user_end != nullptr)user_end();
      isMyScene = false;
      prevScene->begin();
    }

};
