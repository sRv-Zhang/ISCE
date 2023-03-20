#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <list>
#include <stdlib.h>

using namespace std;

#define MAX_BUF_SIZE 512
typedef unsigned char BYTE;

/********************** ȫ�ֺ���intToString ******************
//��һ��Int���͵���ת����һ��string
*************************************************************/
string intToString(int i)
{
	stringstream s;
	s << i;
	return s.str();
}

/***************** ���ݼ�¼�Ľṹ�嶨�� **********************/
struct strMyRecord
{
	BYTE iProtocolType;	                 //02 Э�����ͣ�				���ű��� 3�ࣺicmp tcp udp
	BYTE iService;		                   //03 �������ͣ�				���ű��� 66��
	BYTE iStatusFlag;	                   //04 ״̬��־��				���ű��� 11��
	int  iSrcBytes;		                   //05 Դ��Ŀ���ֽ�����		��������
	int  iDestBytes;	                   //06 Ŀ�ĵ�Դ�ֽ�����		��������
	int  iFailedLogins;	                 //11 ��¼ʧ�ܴ�����			�������� //6����0 ~ 5 
	BYTE bRootShell;	                   //14 �Ƿ���root�û�Ȩ�ޣ�	��ֵ����
	int  iNumofRoot;	                   //16 root�û�Ȩ�޴�ȡ������	��������
	BYTE bGuestLogin;	                   //22 �Ƿ���guest�û���¼��	��ֵ����
	int  iCount;		                     //23 2����������ͬ������Ŀ����������
	int  iSrvCount;		                   //24 2����������ͬ�˿���Ŀ����������
	BYTE iRerrorRate;	                   //27 "REJ"��������������ʣ�����������0 ~ 100
	BYTE iSameSrvRate;	                 //29 ���ӵ���ͬ�˿������ʣ� ����������0 ~ 100
	BYTE iDiffSrvRate;	                 //30 ���ӵ���ͬ�˿������ʣ� ����������0 ~ 100
	int  iDstHostSrvCount;			         //33 ��ͬĿ�ĵ���ͬ�˿���������		��������
	BYTE iDstHostSameSrvRate;		         //34 ��ͬĿ�ĵ���ͬ�˿����������ʣ�	����������0 ~ 100
	BYTE iDstHostDiffSrvRate;		         //35 ��ͬĿ�ĵز�ͬ�˿����������ʣ�	����������0 ~ 100
	BYTE iDstHostSameSrcPortRate;	       //36 ��ͬĿ�ĵ���ͬԴ�˿����ӱ��ʣ�	����������0 ~ 100
	BYTE iDstHostSrvDiffHostRate;	       //37 ��ͬ����������ͬ�˿ڱ��ʣ�		����������0 ~ 100
	BYTE iDstHostSrvSerrorRate;		       //39 ���ӵ�ǰ������S0����ı��ʣ�	����������0 ~ 100
	BYTE iLabel;		                     //42 ���ͱ�ǩ�����ű��� 5��
};
