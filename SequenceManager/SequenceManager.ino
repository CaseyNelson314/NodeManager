#include "SequenceManager.h"
#include "Switch.h"

extern SequenceManager scene0;
extern SequenceManager scene1;
extern SequenceManager scene2;
extern SequenceManager scene3;

//各シーンをつなげる
SequenceManager scene0(&scene1, &scene3);
SequenceManager scene1(&scene2, &scene0);
SequenceManager scene2(&scene3, &scene1);
SequenceManager scene3(&scene0, &scene2);

//入力スイッチ
Switch sw0(3);
Switch sw1(7);

void setup() {
  Serial.begin(115200);

   //コールバック関数セット
  scene0.setMain(func0);
  scene1.setMain(func1);
  scene2.setMain(func2);
  scene3.setMain(func3);

  //自身のシーンからシーケンス制御開始
  scene0.begin();
}

void loop() {
  
  //自身のシーンの場合、セットしたコールバック関数を呼ぶ
  scene0.update();
  scene1.update();
  scene2.update();
  scene3.update();
  
  delay(10);
  
}


//各シーンコールバック関数
void func0() {
  sw0.update();
  sw1.update();
  if (sw0.click())scene0.changeNext(); //次のシーンに切り替え
  if (sw1.click())scene0.changePrev(); //前のシーンに切り替え
  Serial.println("scene0");
}
void func1() {
  sw0.update();
  sw1.update();
  if (sw0.click())scene1.changeNext();
  if (sw1.click())scene1.changePrev();
  Serial.println("scene1");
}
void func2() {
  sw0.update();
  sw1.update();
  if (sw0.click())scene2.changeNext();
  if (sw1.click())scene2.changePrev();
  Serial.println("scene2");
}
void func3() {
  sw0.update();
  sw1.update();
  if (sw0.click())scene3.changeNext();
  if (sw1.click())scene3.changePrev();
  Serial.println("scene3");
}
