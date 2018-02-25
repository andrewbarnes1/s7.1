#include <mbed.h>
#include <EthernetInterface.h>
#include <rtos.h>
//#include <C12832.h>

//C12832 lcd(D11, D13, D12, D7, D10);
int main() {
    EthernetInterface eth;
    UDPSocket udp;

    printf("starting\n");
    //lcd.locate(0, 0);
    //lcd.printf("conecting \n");
    printf("conecting \n");

    eth.connect();
    const char *ip = eth.get_ip_address();
    printf("IP address is: %s\n", ip ? ip : "No IP");

//    lcd.locate(0, 0);
//    lcd.printf("IP address is: %s ", ip ? ip : "No IP");

    /* Open UDP socket and bind to port number to listen to */
    udp.open( &eth);
    udp.bind(65000);
    printf("listening on 65000\n");
//    lcd.printf(" on port 65000");

    while(1){
        char buffer[4*1024];/*4K bytes */
        SocketAddress source;

        /* blocking IO waits for Datagram */
        int l = udp.recvfrom( &source, buffer, sizeof(buffer));

        /* write in zero-byte as string terminator */
        buffer[l]='\0';

        printf("from %s\n", source.get_ip_address());
        printf("  at %d\n", source.get_port());
        printf("data %s\n", buffer);

//        lcd.locate(0,0);
//        lcd.printf("from %s/%d\n", source.get_ip_address(), source.get_port());
//        lcd.printf("\"%s\"",  buffer);

    }
}
