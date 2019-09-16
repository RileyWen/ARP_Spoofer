#ifndef ARP_SPOOFER_NET_STRUCTURE_H
#define ARP_SPOOFER_NET_STRUCTURE_H

#include <cstdio>
#include <cstring>
#include <pcap.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>
#include <algorithm>

const u_char TCP = 0x06;
const u_char UDP = 0x11;

typedef struct ethernet_header {
    u_char dst_mac[6];          // Destination MAC address
    u_char src_mac[6];          // Source MAC address
    u_short type;               // Protocol Type, e.g. 0x0800 for IPv4£¬0x0806 for ARP
} ethernet_header;

/* 4 bytes IP address */
typedef struct ip_address {
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
} ip_address;

/* IPv4 header */
typedef struct ip_header {
    u_char ver_ihl;                 // Version (4 bits) + Internet header length (4 bits)
    u_char tos;                     // Type of service
    u_short total_len;              // Total length
    u_short identification;         // Identification
    u_short flags_fo;               // Flags (3 bits) + Fragment offset (13 bits)
    u_char ttl;                     // Time to live
    u_char proto;                   // Protocol
    u_short crc;                    // Header checksum
    ip_address source_addr;         // Source address
    ip_address destination_addr;    // Destination address
    u_int op_pad;                   // Option + Padding
} ip_header;

/* UDP header*/
typedef struct udp_header {
    u_short sport;              // Source port
    u_short dport;              // Destination port
    u_short len;                // Datagram length
    u_short crc;                // Checksum
} udp_header;

/*TCP header*/
typedef struct tcp_header {
    u_short src_port;
    u_short dst_port;
    u_int seq;
    u_int ack;
    u_char data_offset;  // 4 bits
    u_char flags;
    u_short window_size;
    u_short checksum;
    u_short urgent_p;
} tcp_header;

typedef struct arp_header {
    u_short hardware_type;
    u_short proto_type;
    u_char hardware_size;
    u_char proto_size;
    u_short op_code;
    u_char src_mac[6];
    u_char src_ip[4];
    u_char dst_mac[6];
    u_char dst_ip[4];
} arp_header;

typedef struct arp_packet {
    struct ethernet_header eth_hdr;
    struct arp_header arp_hdr;
    u_char padding[18];     // 'Padding' MUST be added because an Ethernet frame
    //  should be at least 64 bytes. The last 4 bytes of
    //  a frame is FCS, so arp_packet should be padded
    //  60 bytes.
} arp_packet;

// deceive the receiver into thinking that 'target_ip' is at 'sender_mac'.
arp_packet *arp_packet_constructor(u_char cheating_ip[4], u_char mac_of_cheating_ip[6],
                                   u_char receiver_ip[4], u_char receiver_mac[6]);

#endif
