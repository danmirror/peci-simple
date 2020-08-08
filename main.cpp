#include "mySerial.h"
#include <iostream>
using namespace std;



int  main(void)
{

    mySerial serial("/dev/ttyACM0",115200);
    while(1){

    // One Byte At the time
     //serial.Send(128);
     
     

    // An array of byte
    unsigned char  dataArray[] = { 142,0};
    serial.Send("a");

    // Or a string
    //serial.Send("this is it\r\n");
    //serial.Receive(serial,1);
   
}
    return 0;

}

