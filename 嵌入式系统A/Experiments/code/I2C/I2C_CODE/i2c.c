#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/miscdevice.h>

static unsigned short ignore[]      = { I2C_CLIENT_END };
static unsigned short normal_addr[] = { 0x6F, I2C_CLIENT_END };//�豸��ַΪ��01101111��0x6f) ��λ 

static unsigned short force_addr[] = {ANY_I2C_BUS,0x6F, I2C_CLIENT_END};
static unsigned short * forces[] = {force_addr, NULL};

static struct i2c_client_address_data addr_data = {
    .normal_i2c	= normal_addr,   //Ҫ������ַ�źţ����ҵõ�ACK�źţ�����ȷ���Ƿ��������豸
	.probe		= ignore,
    .ignore		= ignore,
    .forces     = forces, //ǿ����Ϊ��������豸
};

static struct i2c_driver SY_driver;

static int major;
static struct class *cls; //�Զ������豸�ڵ� 
struct i2c_client *SY_client;

static ssize_t SY_read(struct file *filp, char __user *buf, size_t count, loff_t * ppos)
{
	int ret=0;
    static volatile unsigned char  values[1]={0};
    

   values[0]=((char)SY_client->addr);
   
   if ( copy_to_user(buf, (void*)values,count )) { //����ֵַbuf�ڴ�����ݴ����û��ռ��values 
      ret = -EFAULT;
	  goto out;
	  }
   out:
      return ret;
}


//�����ַ��豸�ṹ��
static struct file_operations SY_fops = {
    .owner = THIS_MODULE,
	.read  = SY_read,
};

static int SY_detect(struct i2c_adapter *adapter, int address, int kind)
{   
    
    printk("SY_detect\n");
    //����һ��i2c_client�ṹ�壻�շ�������Ҫ������������ .address .adapter .driver
    SY_client = kzalloc(sizeof(struct i2c_client), GFP_KERNEL);
	SY_client->addr    = address;
	SY_client->adapter = adapter;
	SY_client->driver  = &SY_driver;
	strcpy(SY_client->name, "SY");
	i2c_attach_client(SY_client);//��Ҫж������ʱ������� I2C_detach
	printk("SY_probe with name = %s, addr = 0x%x\n", SY_client->name, SY_client->addr);
   
	major = register_chrdev(0, "SY", &SY_fops);//�����ַ��豸���豸�� 

	cls = class_create(THIS_MODULE, "SY");//����һ���� ��Ȼ���������洴��һ���豸 
	class_device_create(cls, NULL, MKDEV(major, 0), NULL, "SY");

	return 0;
}


static int SY_attach(struct i2c_adapter *adapter)
{
	return i2c_probe(adapter, &addr_data, SY_detect);
}

static int SY_detach(struct i2c_client *client)
{
	printk("SY_detach\n");
	class_device_destroy(cls, MKDEV(major, 0));
	class_destroy(cls);
	unregister_chrdev(major, "SY");

	i2c_detach_client(client);//client �ṹ�� 
	kfree(i2c_get_clientdata(client));//�ͷ�client���ڴ� 

	return 0;
}

//����i2c_driver�ṹ�� 
static struct i2c_driver SY_driver = {
	.driver = {
		.name	= "SY",
	},
	.attach_adapter = SY_attach,
	.detach_client  = SY_detach,
};

static int SY_init(void)
{
	printk("SY_init\n");
	i2c_add_driver(&SY_driver);//ע��i2c���� 
	return 0;
}

static void SY_exit(void)
{
	printk("SY_exit\n");
	i2c_del_driver(&SY_driver);
}

module_init(SY_init);
module_exit(SY_exit);
MODULE_LICENSE("GPL");














