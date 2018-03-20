// #include "mbed.h"
// #include "USBHID.h"


// //USBHID hid;
// //HID_REPORT recv;
// //  BusOut leds(LED1,LED2,LED3,LED4);
// // DigitalOut led1(LED1);
// // DigitalOut test_out(D7);
// // DigitalIn start_in(D8,PullDown);
// // PwmOut pwm_out_9(D9);
// // Timer timer;

// Serial pc(SERIAL_TX, SERIAL_RX);

// // main() runs in its own thread in the OS
// int main()
// {
  
    

// pc.printf("\n init\n");
   
    
//     while(1)
//     {
//       /*to main retention, otherwise thread will be died*/
//       /*don't leave empty */
  
//     	//hid.read(&recv);
//      //    leds = recv.data[0];

//         pc.printf("\n hello world\n");
//       wait(1);
//     }

//     return 0;
// }

// #include "mbed.h"
// #include "USBHID.h"
 
//  Serial pc(SERIAL_TX, SERIAL_RX);
// /*
//  * HidTest.c
//  *
//  *  Program to test the UsbHid with HidTest.java
//  *  Java files in USBHID bindings page
//  *
//  *  This test program is allways sending a non blocking message and expecting to read a non blocking message
//  *  Messages are sent with the last byte cycling through '0'-'9' and LED4 toggles with each send
//  *  When a messsage is received:
//  *    LED2 toggles
//  *    Received message is sent, blocking.
//  *    A message is read blocking
//  *    The recived message is now the new non blocking message to be sent
//  *
//  * victorix 04.02.2013
// */
// uint16_t vendor_id=0x1798;
// uint16_t product_id=0x2013;
// uint16_t product_release=0x0001;
// bool connect=true;
// #define HID_LEN 32
 
// USBHID hid(HID_LEN, HID_LEN, vendor_id, product_id, product_release, connect);
// HID_REPORT hidOut;
// HID_REPORT hidIn;
 
// DigitalOut l2(LED2);
// DigitalOut l4(LED3);
 
// int main() {

// pc.printf("\n init\n");


//   char s[HID_LEN]="Have a nice day :)";
//   memcpy(hidOut.data,s,HID_LEN);
//   hidOut.length=HID_LEN;
  
//   hidIn.length=HID_LEN;


//   while(1) {
//     l4=!l4;                 //toggle Led4
//     hid.sendNB(&hidOut);    //send non blocking
//     //last byte used as a simple frame counter
//     if(hidOut.data[HID_LEN-1]>='0' && hidOut.data[HID_LEN-1]<'9')
//       hidOut.data[HID_LEN-1]++;
//     else  hidOut.data[HID_LEN-1]='0';
//     wait(1);                //wait 1s
//     if(hid.readNB(&hidIn)){                  //read non blocking
//       l2=!l2;                                //toggle LED2
//       memcpy(hidOut.data, hidIn.data, hidIn.length);  //copy input to output
//       hid.send(&hidOut);                     //send blocking
//       wait(2);                               //wait 2s
//       if(hid.read(&hidIn)){                  //read blocking
//         memcpy(hidOut.data, hidIn.data, hidIn.length); //copy input to output
//       } 
//     }  
//   }
// }


#include "mbed.h"
#include "USBHID.h"
#include "QEI.h"

uint16_t vendor_id=0x1798;
uint16_t product_id=0x2013;
 
//We declare a USBHID device. Input out output reports have a length of 8 bytes
USBHID hid(8, 8, vendor_id,product_id);
QEI wheel (PA_0, PA_1, NC, 624); 

//This report will contain data to be sent
HID_REPORT send_report;
HID_REPORT recv_report;
 
Serial pc(USBTX, USBRX);
 
int main(void) {
    send_report.length = 8;
 
    while (1) {
        //Fill the report
        for (int i = 0; i < send_report.length; i++) {
            send_report.data[i] = i;//rand() & 0xff;
        }
            
        //Send the report
        hid.send(&send_report);
        
        //try to read a msg
        if(hid.readNB(&recv_report)) {
            pc.printf("recv: ");
            for(int i = 0; i < recv_report.length; i++) {
                pc.printf("%d ", recv_report.data[i]);
            }
            pc.printf("\r\n");
        }

        pc.printf("ENCODER Pulses is: %i\n", wheel.getPulses());
        
        wait(0.1);
    }
}
