#include <EZExpander.h>

EZExpander expander = EZExpander();

void setup() {
	randomSeed(analogRead(0));
}

void loop() {
  byte n = random(1,6);
  for(int j=0;j<n;j++) {
  	for(int i=20;i<=35;i++) {
      expander.digitalWrite(i, HIGH);
      delay(20);
    }
    for(int i=20;i<=35;i++) {
      expander.digitalWrite(i, LOW);
      delay(20);
    }
  }
  n = random(1,6);
  for(int j=0;j<n;j++) {
  	for(int i=20;i<=35;i++) {
      for(int k=20;k<=35;k++) {
        if (k == i) {
          expander.digitalWrite(k, HIGH);
        } else {
          expander.digitalWrite(k, LOW);
        }
      }
      delay(10);
    }
  }


  for(int i=20;i<=35;i++) {
    expander.digitalWrite(i, LOW);
  }
}
