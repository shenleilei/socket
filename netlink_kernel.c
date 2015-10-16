#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/init.h>
#include <linux/ip.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/netlink.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Koorey King");
struct nlmsghdr *nlh=NULL;
struct sock *nl_sk = NULL;
static void nl_data_ready (struct sk_buff *skb)
{

    while(skb  != NULL)
    {
          nlh = (struct nlmsghdr *)skb->data;
          printk("%s: received netlink message payload: %s \n", __FUNCTION__, (char*)NLMSG_DATA(nlh));
		  skb=NULL;
          //kfree_skb(skb);
    }
    printk("recvied finished!\n");
}

static int __init myinit_module(void)
{
    printk("my netlink in\n");
	//struct net *net;
	struct netlink_kernel_cfg cfg = {
		.input = nl_data_ready,
	};
    nl_sk = netlink_kernel_create(&init_net,NETLINK_TEST,&cfg);
    return 0;
}

static void __exit mycleanup_module(void)
{
    printk("my netlink out!\n");
    sock_release(nl_sk->sk_socket);
}

module_init(myinit_module);
module_exit(mycleanup_module);
