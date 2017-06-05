void  pinInitial(Chain *ptrchain){
    pinMode(ptrchain->controlPin.controlPin1,OUTPUT);
    pinMode(ptrchain->controlPin.controlPin2,OUTPUT);
    pinMode(ptrchain->controlPin.controlPin3,OUTPUT);
    digitalWrite(ptrchain->controlPin.controlPin1,LOW);
    digitalWrite(ptrchain->controlPin.controlPin2,LOW);
    digitalWrite(ptrchain->controlPin.controlPin3,LOW);  
}

void  pinActive(int pinNumber,boolean act){
    digitalWrite(pinNumber, act);
}

