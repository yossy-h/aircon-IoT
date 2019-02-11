int ir_out = 3;
byte str=0;

//暖房
unsigned int dh[] = {/*ここに赤外線のデータ*/};
//停止
unsigned int ds[] = {/*ここに赤外線のデータ*/};


void setup() { 
        pinMode(ir_out, OUTPUT); 
        Serial.begin(9600);
}

//暖房起動
void heater() {
  int dataSize = sizeof(dh) / sizeof(dh[0]);
  for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = dh[cnt]*10;
    unsigned long us = micros();
    do {
      digitalWrite(ir_out, 1 - (cnt&1));
      delayMicroseconds(8);
      digitalWrite(ir_out, 0);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0); 
  }
}

//エアコン停止
void stop() {
  int dataSize = sizeof(ds) / sizeof(ds[0]);
  for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = ds[cnt]*10;
    unsigned long us = micros();
    do {
      digitalWrite(ir_out, 1 - (cnt&1)); 
      delayMicroseconds(8); 
      digitalWrite(ir_out, 0);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0); 
  }
}

void loop() {

        if(Serial.available() > 0){

                str = Serial.read();

                if(str == 'h'){
                        heater();
                        str = 0;
                }//hが送られてきたら暖房起動

                else if(str == 's'){
                        stop();
                        str = 0;
                }//sが送られてきたらエアコン停止
        }
        //delay(1000);
}