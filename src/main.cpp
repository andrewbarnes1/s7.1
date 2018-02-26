#include <mbed.h>
#include <EthernetInterface.h>
#include <rtos.h>

#include <C12832.h>
char buffer[1024]; /* 1k bytes */

int main() {
    C12832 lcd(D11, D13, D12, D7, D10);
    EthernetInterface eth; //Create the ethernetInterface
    UDPSocket udp; //Create the UDP Socket

    printf("connecting on DHCP\n");
    eth.connect();
    // Connect to the internet
    const char *ip = eth.get_ip_address();
    printf("IP address is: %s\n", ip ? ip : "No IP");

    //Create the UDP socket
    udp.open( &eth);

    /* Listen for UDP on port 65000 */
    udp.bind(65000);

    printf("listening on 65000\n");

    while(1){
        SocketAddress source;
        int len = udp.recvfrom( &source, buffer, sizeof(buffer));
        buffer[len]='\0';

        printf("message from %s/%d \n", source.get_ip_address(), source.get_port());
        lcd.locate(0,0);
        lcd.printf("\"%s\"", buffer);
    }
}
