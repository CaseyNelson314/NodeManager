#include "Node.h"
#include "Switch.h"

extern Node scene0;
extern Node scene1;
extern Node scene2;
extern Node scene3;

//各シーンをつなげる
Node scene0(scene1, scene3);
Node scene1(scene2, scene0);
Node scene2(scene3, scene1);
Node scene3(scene0, scene2);

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

  //自身のシーンから開始
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


void changeScene(Node &current) {
  sw0.update();
  sw1.update();
  if (sw0.click())current.changeNext();
  if (sw1.click())current.changePrev();
}

//各シーンコールバック関数
void func0() {
  Serial.println("scene0");
  changeScene(scene0);
}
void func1() {
  Serial.println("scene1");
  changeScene(scene1);
}
void func2() {
  Serial.println("scene2");
  changeScene(scene2);
}
void func3() {
  Serial.println("scene3");
  changeScene(scene3);
}
