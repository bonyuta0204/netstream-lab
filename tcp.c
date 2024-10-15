#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <unistd.h>

// TCPヘッダーのチェックサム計算
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main() {
    // Raw socket作成
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    char packet[4096];
    struct iphdr *iph = (struct iphdr *)packet;
    struct tcphdr *tcph = (struct tcphdr *)(packet + sizeof(struct iphdr));

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(80);  // 送信先ポート
    dest.sin_addr.s_addr = inet_addr("192.168.1.1");  // 送信先IP

    memset(packet, 0, 4096);

    // IPヘッダー
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
    iph->id = htonl(54321);
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_TCP;
    iph->saddr = inet_addr("192.168.1.2");  // 自分のIP
    iph->daddr = dest.sin_addr.s_addr;

    iph->check = checksum((unsigned short *)packet, iph->tot_len);

    // TCPヘッダー
    tcph->source = htons(12345);  // 送信元ポート
    tcph->dest = htons(80);  // 送信先ポート
    tcph->seq = 0;
    tcph->ack_seq = 0;
    tcph->doff = 5;  // TCPヘッダーのサイズ
    tcph->fin = 0;
    tcph->syn = 1;  // SYNフラグを立てる
    tcph->rst = 0;
    tcph->psh = 0;
    tcph->ack = 0;
    tcph->urg = 0;
    tcph->window = htons(5840); /* サイズ */
    tcph->check = 0;
    tcph->urg_ptr = 0;

    tcph->check = checksum((unsigned short *)tcph, sizeof(struct tcphdr));

    // パケット送信
    if (sendto(sock, packet, iph->tot_len, 0, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
        perror("Send failed");
    } else {
        printf("Packet Sent!\n");
    }

    close(sock);
    return 0;
}

