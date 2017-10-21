#pragma execution_character_set("utf-8")

#ifndef _V_ECANVCI_H_                                        
#define _V_ECANVCI_H_


#include "windows.h"
//#include "windef.h"//MinGW
#include <QtDebug>

#define Dll_EXPORTS

//�ӿڿ����Ͷ���

#define USBCAN1		3
#define USBCAN2		4

//CAN������
#define	ERR_CAN_OVERFLOW			0x0001	//CAN�������ڲ�FIFO���
#define	ERR_CAN_ERRALARM			0x0002	//CAN���������󱨾�
#define	ERR_CAN_PASSIVE				0x0004	//CAN��������������
#define	ERR_CAN_LOSE				0x0008	//CAN�������ٲö�ʧ
#define	ERR_CAN_BUSERR				0x0010	//CAN���������ߴ���
#define	ERR_CAN_REG_FULL			0x0020	//CAN���ռĴ�����
#define	ERR_CAN_REG_OVER			0x0040	//CAN���ռĴ������
#define	ERR_CAN_ZHUDONG	    		0x0080	//CAN��������������

//ͨ�ô�����
#define	ERR_DEVICEOPENED			0x0100	//�豸�Ѿ���
#define	ERR_DEVICEOPEN				0x0200	//���豸����
#define	ERR_DEVICENOTOPEN			0x0400	//�豸û�д�
#define	ERR_BUFFEROVERFLOW			0x0800	//���������
#define	ERR_DEVICENOTEXIST			0x1000	//���豸������
#define	ERR_LOADKERNELDLL			0x2000	//װ�ض�̬��ʧ��
#define ERR_CMDFAILED				0x4000	//ִ������ʧ�ܴ�����
#define	ERR_BUFFERCREATE			0x8000	//�ڴ治��


//�������÷���״ֵ̬
#define	STATUS_OK					1
#define STATUS_ERR					0
	
#define CMD_DESIP			0
#define CMD_DESPORT			1
#define CMD_CHGDESIPANDPORT		2


//1.ZLGCANϵ�нӿڿ���Ϣ���������͡�
typedef  struct  _BOARD_INFO{
		USHORT	hw_Version;
		USHORT	fw_Version;
		USHORT	dr_Version;
		USHORT	in_Version;
		USHORT	irq_Num;
		BYTE	can_Num;
		CHAR	str_Serial_Num[20];
		CHAR	str_hw_Type[40];
		USHORT	Reserved[4];
} BOARD_INFO,*P_BOARD_INFO; 

//2.����CAN��Ϣ֡���������͡�
typedef  struct  _CAN_OBJ{
	UINT	ID;
	UINT	TimeStamp;
	BYTE	TimeFlag;
	BYTE	SendType;
	BYTE	RemoteFlag;//�Ƿ���Զ��֡
	BYTE	ExternFlag;//�Ƿ�����չ֡
	BYTE	DataLen;
	BYTE	Data[8];
	BYTE	Reserved[3];
}CAN_OBJ,*P_CAN_OBJ;

//3.����CAN������״̬���������͡�
typedef struct _CAN_STATUS{
	UCHAR	ErrInterrupt;
	UCHAR	regMode;
	UCHAR	regStatus;
	UCHAR	regALCapture;
	UCHAR	regECCapture; 
	UCHAR	regEWLimit;
	UCHAR	regRECounter; 
	UCHAR	regTECounter;
	DWORD	Reserved;
}CAN_STATUS,*P_CAN_STATUS;

//4.���������Ϣ���������͡�
typedef struct _ERR_INFO{
		UINT	ErrCode;
		BYTE	Passive_ErrData[3];
		BYTE	ArLost_ErrData;
} ERR_INFO,*P_ERR_INFO;

//5.�����ʼ��CAN����������
typedef struct _INIT_CONFIG{
	DWORD	AccCode;
	DWORD	AccMask;
	DWORD	Reserved;
	UCHAR	Filter;
	UCHAR	Timing0;	
	UCHAR	Timing1;	
	UCHAR	Mode;
}INIT_CONFIG,*P_INIT_CONFIG;

typedef struct _tagChgDesIPAndPort
{
	char szpwd[10];
	char szdesip[20];
	int desport;
}CHGDESIPANDPORT;

///////// new add struct for filter /////////
typedef struct _FILTER_RECORD{
	DWORD ExtFrame;	//�Ƿ�Ϊ��չ֡
	DWORD Start;
	DWORD End;
}FILTER_RECORD,*P_FILTER_RECORD;


#ifdef Dll_EXPORTS
	#define DllAPI __declspec(dllexport)
#else
	#define DllAPI __declspec(dllimport)

#endif

#define EXTERNC	 extern "C"
#define CALL __stdcall//__cdecl

//extern "C"
//{

EXTERNC	DllAPI DWORD CALL OpenDevice(DWORD DeviceType,DWORD DeviceInd,DWORD Reserved);
EXTERNC DllAPI DWORD CALL CloseDevice(DWORD DeviceType,DWORD DeviceInd);

EXTERNC DllAPI DWORD CALL InitCAN(DWORD DeviceType, DWORD DeviceInd, DWORD CANInd, P_INIT_CONFIG pInitConfig);

EXTERNC DllAPI DWORD CALL ReadBoardInfo(DWORD DeviceType,DWORD DeviceInd,P_BOARD_INFO pInfo);
EXTERNC DllAPI DWORD CALL ReadErrInfo(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,P_ERR_INFO pErrInfo);
EXTERNC DllAPI DWORD CALL ReadCANStatus(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,P_CAN_STATUS pCANStatus);

EXTERNC DllAPI DWORD CALL GetReference(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,DWORD RefType,PVOID pData);
EXTERNC DllAPI DWORD CALL SetReference(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,DWORD RefType,PVOID pData);

EXTERNC DllAPI ULONG CALL GetReceiveNum(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);
EXTERNC DllAPI DWORD CALL ClearBuffer(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);

EXTERNC DllAPI DWORD CALL StartCAN(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);
EXTERNC DllAPI DWORD CALL ResetCAN(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);

EXTERNC DllAPI ULONG CALL Transmit(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,P_CAN_OBJ pSend,ULONG Len);
EXTERNC DllAPI ULONG CALL Receive(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,P_CAN_OBJ pReceive,ULONG Len,INT WaitTime);

class ECan
{
public:
    /*�豸��*/
    int nDeviceType; // USBCAN-II
    /*������*/
    int nDeviceInd;
    /*ͨ����Ϊ0*/
    int nReserved;
    /*canͨ����^can1 = 1,can2 = 2^*/
    int nCANInd;
    /*���ó�ʼ���ṹ��*/
    INIT_CONFIG vic;
    /*USBCAN����Ϣ�ṹ��*/
    BOARD_INFO vbi;
    /*�������ݽṹ��*/
    CAN_OBJ nTransmitData;
    /*���ڽ������ݵĽṹ��*/
    CAN_OBJ nReceiveData[100];  //��ʱ��100��
    /*���ܳ�ʱʱ��,�Ժ���Ϊ��λ*/
    BYTE nReceiveTime;
public:
    ECan()
    {
        nDeviceType = 4; // USBCAN-II
        nDeviceInd = 0;  // Ĭ��Ϊ0
        nReserved = 0;   // Ĭ��Ϊ0
        nCANInd = 0;
        nReceiveTime = 250;

        ZeroMemory(&vic, sizeof(INIT_CONFIG));
        ZeroMemory(&vbi, sizeof(BOARD_INFO));
        ZeroMemory(&nTransmitData, sizeof(CAN_OBJ));
        vic.AccMask = 0xffffffff;
        vic.Filter = 0;//��ʹ���˲�
        vic.Mode = 0; //0��ʾ����ģʽ��1��ʾֻ��ģʽ
        /*��������Ϊ250Kbps*/
        vic.Timing0 = 0x01;
        vic.Timing1 = 0x1c;

        DWORD dwRel;
        Sleep(100);
        dwRel = ECanOpenDevice();
        if (dwRel != STATUS_OK)
        {
            qDebug() << "��USBCANʧ��\n";
            return ;
        }
        else
        {
            qDebug() << "��USBCAN�ɹ�\n";
        }
        Sleep(100);
        dwRel = ECanInitCAN();
        Sleep(100);
        ClearBuffer(nDeviceType, nDeviceInd, nCANInd);
        if (dwRel != STATUS_OK)
        {
            qDebug() << "��ʼ��USBCANʧ��\n";
            ECanCloseDevice();
            qDebug() << "USBCAN�豸�Ѿ��ر�\n";
            return ;
        }
        else
        {
            qDebug() << "��ʼ��USBCAN�ɹ�\n";
        }
        Sleep(100);
        dwRel = ECanReadBoardInfo();
        if(dwRel != STATUS_OK)
        {
            qDebug() << "��ȡUSBCAN�Ļ�����Ϣʧ��\n";
            ZeroMemory(&vbi, sizeof(BOARD_INFO));
        }
        else
        {
            qDebug() << "��ȡUSBCAN�Ļ�����Ϣ�ɹ�\n";
        }
        Sleep(100);
        dwRel = ECanStartCAN();
        if (dwRel != STATUS_OK)
        {
            qDebug() << "USBCAN����ʧ��\n";
            ZeroMemory(&vbi, sizeof(BOARD_INFO));
            ECanCloseDevice();
            qDebug() << "USBCAN�豸�Ѿ��ر�\n";
        }
        else
        {
            qDebug() << "USBCAN�����ɹ�\n";
        }
        Sleep(1000);
    }
    ~ECan()
    {
        ECanCloseDevice();
    }
    void ECanReset()
    {
        nDeviceType = 4; // USBCAN-II
        nDeviceInd = 0;  // Ĭ��Ϊ0
        nReserved = 0;   // Ĭ��Ϊ0
        nCANInd = 0;
        nReceiveTime = 250;

        ZeroMemory(&vic, sizeof(INIT_CONFIG));
        ZeroMemory(&vbi, sizeof(BOARD_INFO));
        ZeroMemory(&nTransmitData, sizeof(CAN_OBJ));
        vic.AccMask = 0xffffffff;
        vic.Filter = 0;//��ʹ���˲�
        vic.Mode = 0; //0��ʾ����ģʽ��1��ʾֻ��ģʽ
                      /*��������Ϊ250Kbps*/
        vic.Timing0 = 0x01;
        vic.Timing1 = 0x1c;

        DWORD dwRel;
        Sleep(100);
        dwRel = ECanOpenDevice();
        if (dwRel != STATUS_OK)
        {
            qDebug() << "��USBCANʧ��\n";
            return;
        }
        else
        {
            qDebug() << "��USBCAN�ɹ�\n";
        }
        Sleep(100);
        dwRel = ECanInitCAN();
        Sleep(100);
        ClearBuffer(nDeviceType, nDeviceInd, nCANInd);
        if (dwRel != STATUS_OK)
        {
            qDebug() << "��ʼ��USBCANʧ��\n";
            ECanCloseDevice();
            qDebug() << "USBCAN�豸�Ѿ��ر�\n";
            return;
        }
        else
        {
            qDebug() << "��ʼ��USBCAN�ɹ�\n";
        }
        Sleep(100);
        dwRel = ECanReadBoardInfo();
        if (dwRel != STATUS_OK)
        {
            qDebug() << "��ȡUSBCAN�Ļ�����Ϣʧ��\n";
            ZeroMemory(&vbi, sizeof(BOARD_INFO));
        }
        else
        {
            qDebug() << "��ȡUSBCAN�Ļ�����Ϣ�ɹ�\n";
        }
        Sleep(100);
        dwRel = ECanStartCAN();
        if (dwRel != STATUS_OK)
        {
            qDebug() << "USBCAN����ʧ��\n";
            ZeroMemory(&vbi, sizeof(BOARD_INFO));
            ECanCloseDevice();
            qDebug() << "USBCAN�豸�Ѿ��ر�\n";
        }
        else
        {
            qDebug() << "USBCAN�����ɹ�\n";
        }
        Sleep(1000);
    }
    DWORD ECanOpenDevice()
    {
        return OpenDevice(nDeviceType, nDeviceInd, nReserved);
    }
    DWORD ECanCloseDevice()
    {
        return CloseDevice(nDeviceType, nDeviceInd);
    }
    DWORD ECanInitCAN()
    {
        return InitCAN(nDeviceType, nDeviceInd, nCANInd,&vic);
    }
    DWORD ECanStartCAN()
    {
        return StartCAN(nDeviceType, nDeviceInd, nCANInd);
    }
    DWORD ECanTransmit(UINT id,BYTE sendtype, BYTE remoteflag, BYTE externflag, BYTE datalen,BYTE data[8])
    {
        nTransmitData.ID = id;
        nTransmitData.SendType = sendtype;        //����֡����
        nTransmitData.RemoteFlag = remoteflag;    //�Ƿ���Զ��֡ =0ʱΪ����֡��=1ʱΪԶ��֡
        nTransmitData.ExternFlag = externflag;    //�Ƿ�����չ֡ =0ʱΪ��׼֡��11λ֡ID��=1ʱΪ��չ֡��29λ֡ID��
        nTransmitData.DataLen = datalen;          //���ݳ���    <=8
        int i = 0;
        for (i = 0; i < datalen; i++)
        {
            nTransmitData.Data[i] = data[i];
        }
        for ( ; i < 8; i++)
        {
            nTransmitData.Data[i] =0xff;
        }
        return Transmit(nDeviceType, nDeviceInd, nCANInd,&nTransmitData, 1);
    }
    /*���ú��������ݽ�����nReceiveData[]����*/
    DWORD ECanReceive()
    {
        /*��������*/
        Sleep(100);
    //	ECanStartCAN();
        int DwRel = GetReceiveNum(nDeviceType, nDeviceInd, nCANInd);
        for (int i = 0; i < DwRel; i++)
        {
            ZeroMemory((nReceiveData + i), sizeof(CAN_OBJ));
        }
        if(DwRel != 0)
        {
            /*����ʵ�ʶ�ȡ����֡�����������ֵΪ0xFFFFFFFF�����ʾ��ȡ����ʧ�ܣ��д������������ReadErrInfo��������ȡ������*/
            int DwRell = Receive(nDeviceType, nDeviceInd, nCANInd, nReceiveData, 100, nReceiveTime);
            ClearBuffer(nDeviceType, nDeviceInd, nCANInd);
        //	ResetCAN(nDeviceType, nDeviceInd, nCANInd);
            return  DwRell;
        }
        //ResetCAN(nDeviceType, nDeviceInd, nCANInd);

        return 0;
    }
    DWORD ECanReadBoardInfo()
    {
        return ReadBoardInfo(nDeviceType, nDeviceInd, &vbi);
    }
};

#endif
