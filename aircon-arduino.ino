int ir_out = 3;
byte str=0;

//�g�[
unsigned int dh[] = {/*�����ɐԊO���̃f�[�^*/};
//��~
unsigned int ds[] = {/*�����ɐԊO���̃f�[�^*/};


void setup() { 
        pinMode(ir_out, OUTPUT); 
        Serial.begin(9600);
}

//�g�[�N��
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

//�G�A�R����~
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
                }//h�������Ă�����g�[�N��

                else if(str == 's'){
                        stop();
                        str = 0;
                }//s�������Ă�����G�A�R����~
        }
        //delay(1000);
}