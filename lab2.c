// Tim Whitaker & Jason Boutte

#define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_link.h>

int main(int argc, char *argv[])
{
   struct ifaddrs *ifaddr, *ifa;
   int family, s, n;
   char host[NI_MAXHOST];

   if (getifaddrs(&ifaddr) == -1) {
       perror("getifaddrs");
       exit(EXIT_FAILURE);
   }

   for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
       if (ifa->ifa_addr == NULL)
           continue;

       family = ifa->ifa_addr->sa_family;

       /* Display interface name and family (including symbolic
          form of the latter for the common families) */

       printf("%-8s %s (%d)\t",
              ifa->ifa_name,
              (family == AF_PACKET) ? "AF_PACKET" :
              (family == AF_INET) ? "AF_INET" :
              (family == AF_INET6) ? "AF_INET6" : "???",
              family);

       /* For an AF_INET* interface address, display the address */

       if (family == AF_INET || family == AF_INET6) {
           s = getnameinfo(ifa->ifa_addr,
                   (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                         sizeof(struct sockaddr_in6),
                   host, NI_MAXHOST,
                   NULL, 0, NI_NUMERICHOST);
           if (s != 0) {
               printf("getnameinfo() failed: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }

           printf("\t %s\n", host);

       } else if (family == AF_PACKET && ifa->ifa_data != NULL) {
           struct rtnl_link_stats *stats = ifa->ifa_data;
            

           //IFA_data gives info on AF_Packets like how many packets and bytes were sent
           //I want just a general address from AF_PACKET though.
           //I've tried using the getnameinfo function but haven't made it work.
           //just printing ifa_addr is not what I want either.
           //I think I need to find another function.
           //There's also some member vars that look good like ifu_dstnaddr
           //Now it's getting late and I can''t ssh into jaguar for some reason.
           //I keep getting timed out trying to log in.
           //It's looking like I won't be able to test anymore until tomorrow.
           //I figure these comments will help my train of thought at the very least.
           //I've been talking to my partner Jason and am not sure if he's gotten much farther than where I am now.
           //I figure I'll turn this in anyways to make sure we get something in. If we figure it out from here, we'll resubmit.

       }
   }

   freeifaddrs(ifaddr);
   exit(EXIT_SUCCESS);
}
