#include "DataPreTreat.h"

int main(int argc,char* argv[])
{
	/************************************** �������� ********************************************/
	
	const char* Datatreat = "_datatreat";                     //Ԥ��������ļ���׺
	char* InputFileName,*OutputFileName;                      //Ԥ���������ļ���������ļ���
	FILE *pInFile, *pOutFile;                                 //�����ļ�������ļ���ָ��
	
	int i;
  int iRcdCount = 0;                                        //���ݼ�¼����Ŀ	

	char szBuf[MAX_BUF_SIZE];                                 //MAX_BUF_SIZE = 512	
	strMyRecord* pRecord;                                     //�������ݼ�¼��ָ��
	
	list <strMyRecord*> RecordList;                           //���ݼ�¼����
	list<strMyRecord*>::iterator RecdIter;                    //������¼�����ĵ�����
	
	string strTmp,strTmp2;
	string StrRecord, StrTemp;
	char szSeps[] = ",\r\n";
	
	
	//�ж�main���������Ƿ���ȷ
	if (argc != 2) 
	{
		cout<<"Parameter error !"<<endl;
		return -1;
	}
	
	/********************************* ��Ԥ���������ļ� **************************************/
	InputFileName = new char[30];
	strcpy(InputFileName,argv[1]);
	
	if ((pInFile = fopen(InputFileName, "r")) == NULL)              //kddcup99.data_10000
	{
		cout<<"Open training-data file faied !"<<endl;
		return -1;
	}
	
	/********************************* ��Ԥ��������ļ� **************************************/
	//ƴдԤ����������ɺ������ļ��������ڴ򿪵������ļ�����Ϻ�׺_datatreat
	OutputFileName = strcat(InputFileName,Datatreat);

	if ((pOutFile = fopen(OutputFileName, "w")) == NULL)   //kddcup99.data_10000_datatreat
	{
		fclose(pInFile);
		cout<<"Creat Data-preterat file failed!"<<endl;
		return -1;
	}
	
	/*********************** ��һ���� ѭ����ȡ����,�����й���************************************
	1����ȡ�ļ��е�ÿһ����¼����������
	2��ѡ��Ծ�����������ԣ���������Ҫ������
	*********************************************************************************************/
  cout<<"Start reading records from "<<argv[1]<<"..."<<endl;
  
	while (fgets(szBuf, MAX_BUF_SIZE, pInFile) != NULL)
	{
		//ÿ��1000 ����ʾ��������
		if (++iRcdCount%10000 == 0)
			cout<<setiosflags(ios::left)<<"---------- "<<setw(8)<<iRcdCount<<" lines have read ----------"<<endl;
		
		//�����µļ�¼�ڵ�
		pRecord = new strMyRecord;
		
		/********* ����ѡ����20�У����аٷֱ���ֵȫ��ת��Ϊ�ٷ�������ǩ�кϲ�Ϊ5�� ***********/
		
		//��1�в�Ҫ
		strtok(szBuf, szSeps);
		
		//��2�У�Э������
		strTmp = strtok(NULL, szSeps);
		//��Protocol���Եķ��������ֶθ�Ϊö�������ֶ�
		if(strTmp == "icmp")
			pRecord->iProtocolType = 1;
		else if(strTmp == "tcp")
			pRecord->iProtocolType = 2;
		else if(strTmp == "udp")
			pRecord->iProtocolType = 3;
		else
			pRecord->iProtocolType = 4;
		
		
		//��3�У���������
		strTmp = strtok(NULL, szSeps);
		//��Service���Եķ��������ֶθ�Ϊö�������ֶ�
		if(strTmp == "domain_u")
			pRecord->iService = 1;
		else if(strTmp == "ecr_i")
			pRecord->iService = 2;
		else if(strTmp == "eco_i")
			pRecord->iService = 3;
		else if(strTmp == "finger")
			pRecord->iService = 4;
		else if(strTmp == "ftp_data")
			pRecord->iService = 5;
		else if(strTmp == "ftp")
			pRecord->iService = 6;
		else if(strTmp == "http")
			pRecord->iService = 7;
		else if(strTmp == "hostnames")
			pRecord->iService = 8;
		else if(strTmp == "imap4")
			pRecord->iService = 9;
		else if(strTmp == "login")
			pRecord->iService = 10;
		else if(strTmp == "mtp")
			pRecord->iService = 11;
		else if(strTmp == "netstat")
			pRecord->iService = 12;
		else if(strTmp == "other")
			pRecord->iService = 13;
		else if(strTmp == "private")
			pRecord->iService = 14;
		else if(strTmp == "smtp")
			pRecord->iService = 15;
		else if(strTmp == "systat")
			pRecord->iService = 16;
		else if(strTmp == "telnet")
			pRecord->iService = 17;
		else if(strTmp == "time")
			pRecord->iService = 18;
		else if(strTmp == "uucp")
			pRecord->iService = 19;
		else
			pRecord->iService = 20;

    		
		//��4�У�״̬��־
		strTmp = strtok(NULL, szSeps);
		//��StatusFlag���Եķ��������ֶθ�Ϊö�������ֶ�
		if(strTmp == "REJ")
			pRecord->iStatusFlag = 1;
		else if(strTmp == "RSTO")
			pRecord->iStatusFlag = 2;
		else if(strTmp == "RSTR")
			pRecord->iStatusFlag = 3;
		else if(strTmp == "S0")
			pRecord->iStatusFlag = 4;
		else if(strTmp == "S3")
			pRecord->iStatusFlag = 5;
		else if(strTmp == "SF")
			pRecord->iStatusFlag = 6;
		else if(strTmp == "SH")
			pRecord->iStatusFlag = 7;
		else
			pRecord->iStatusFlag = 8;
		

		//��5�У�Դ��Ŀ���ֽ���
		strTmp = strtok(NULL, szSeps);
		pRecord->iSrcBytes = atoi(strTmp.c_str());
		//��6�У�Ŀ�ĵ�Դ�ֽ���
		strTmp = strtok(NULL, szSeps);
		pRecord->iDestBytes = atoi(strTmp.c_str());
		//��7��8��9��10�в�Ҫ
		for (i=0; i<4; i++)
			strtok(NULL, szSeps); // 7-10
		//��11�У���¼ʧ�ܴ���
		strTmp = strtok(NULL, szSeps);
		pRecord->iFailedLogins = atoi(strTmp.c_str());
		//��12��13�в�Ҫ
		strtok(NULL, szSeps); // 12
		strtok(NULL, szSeps); // 13
		//��14�У��Ƿ���root�û�Ȩ��
		strTmp = strtok(NULL, szSeps);
		pRecord->bRootShell = atoi(strTmp.c_str());
		//��15�в�Ҫ
		strtok(NULL, szSeps); // 15
		//��16�У�root�û�Ȩ�޴�ȡ����
		strTmp = strtok(NULL, szSeps);
		pRecord->iNumofRoot = atoi(strTmp.c_str());
		//��17��18��19��20��21�в�Ҫ
		for (i=0; i< 5; i++)
			strtok(NULL, szSeps); // 17-21 
		//��22�У��Ƿ���guest�û���¼
		strTmp = strtok(NULL, szSeps);
		pRecord->bGuestLogin = atoi(strTmp.c_str());
		//��23�У�2����������ͬ������Ŀ
		strTmp = strtok(NULL, szSeps);
		pRecord->iCount = atoi(strTmp.c_str());
		//��24�У�2����������ͬ�˿���Ŀ
		strTmp = strtok(NULL, szSeps);
		pRecord->iSrvCount = atoi(strTmp.c_str());
		//��25��26�в�Ҫ
		strtok(NULL, szSeps); // 25
		strtok(NULL, szSeps); // 26
		//��27�У�"REJ"���������������
		strTmp = strtok(NULL, szSeps);
		//��0~1��С����ת����0��100֮�������
		strTmp[1] = strTmp[2]; 
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iRerrorRate = atoi(strTmp.c_str());

		//��28�в�Ҫ
		strtok(NULL, szSeps); // 28
		//��29�У����ӵ���ͬ�˿�������
		strTmp = strtok(NULL, szSeps);	
		strTmp[1] = strTmp[2]; 
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iSameSrvRate = atoi(strTmp.c_str());

		
		//��30�У����ӵ���ͬ�˿�������
		strTmp = strtok(NULL, szSeps);
		strTmp[1] = strTmp[2]; 
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDiffSrvRate = atoi(strTmp.c_str());
		
		//��31��32�в�Ҫ
		strtok(NULL, szSeps); // 31
		strtok(NULL, szSeps); // 32
		//��33�У���ͬĿ�ĵ���ͬ�˿�������
		strTmp = strtok(NULL, szSeps);
		pRecord->iDstHostSrvCount = atoi(strTmp.c_str());
		//��34�У���ͬĿ�ĵ���ͬ�˿�����������
		strTmp = strtok(NULL, szSeps);				
		strTmp[1] = strTmp[2]; 
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostSameSrvRate = atoi(strTmp.c_str());

		
		//��35�У���ͬĿ�ĵز�ͬ�˿�����������
		strTmp = strtok(NULL, szSeps);		
		strTmp[1] = strTmp[2]; 
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostDiffSrvRate = atoi(strTmp.c_str());		
		
		//��36�У���ͬĿ�ĵ���ͬԴ�˿����ӱ���
		strTmp = strtok(NULL, szSeps);	  
	  strTmp[1] = strTmp[2]; 
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostSameSrcPortRate = atoi(strTmp.c_str());
		
		//��37�У���ͬ����������ͬ�˿ڱ���
		strTmp = strtok(NULL, szSeps);		
	  strTmp[1] = strTmp[2]; 
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostSrvDiffHostRate = atoi(strTmp.c_str());	
				
		//��38�в�Ҫ
		strtok(NULL, szSeps); // 38
		//��39�У����ӵ�ǰ������S0����ı���
		strTmp = strtok(NULL, szSeps);		
	  strTmp[1] = strTmp[2]; 
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostSrvSerrorRate = atoi(strTmp.c_str());
		
		//��40��41�в�Ҫ
		strtok(NULL, szSeps); // 40
		strtok(NULL, szSeps); // 41
		//��42�У����ͱ�ǩ ��Ϊ5��
		strTmp.clear();
		strTmp = strtok(NULL, szSeps);
				
		if (strTmp == "normal.")
			pRecord->iLabel = 0; //normal
		else if ((strTmp == "smurf.") || (strTmp == "neptune.") || (strTmp == "back.") || (strTmp == "teardrop.") || (strTmp == "pod.") || (strTmp == "land."))
			pRecord->iLabel = 1; //dos
		else if ((strTmp == "satan.") || (strTmp == "ipsweep.") || (strTmp == "portsweep.") || (strTmp == "nmap."))
			pRecord->iLabel = 2; //probe
		else if ((strTmp == "buffer_overflow.") || (strTmp == "rootkit.") || (strTmp == "loadmodule.") || (strTmp == "perl."))
				pRecord->iLabel = 3; //u2r
		else if ((strTmp == "ftp_write.") || (strTmp == "guess_passwd.") || (strTmp == "imap.") || (strTmp == "multihop.") || (strTmp == "phf.") || (strTmp == "spy.") || (strTmp == "warezclient.") || (strTmp == "warezmaster."))
				pRecord->iLabel = 4; //r2l
		    
		//������β�������¼
		RecordList.push_back(pRecord);	
	}
	
	//�ļ���ȡ��ϣ���ʾ��¼��	
	cout<<"All Records have read ! Total "<<iRcdCount<<" records !"<<endl;
	

         
  /*********************** �ڶ����� ��������������¼д������ļ��� ************************************/
  cout<<"Start writing records into "<<OutputFileName;
  cout<<" ..."<<endl;
  
	//������������ÿһ����������ļ�¼��д��Ԥ��������ļ�
	for (i=0,RecdIter = RecordList.begin(); RecdIter != RecordList.end(); RecdIter++)
	{
		if (++i%10000 == 0) //&& (IsPrintLog == true))
			cout<<setiosflags(ios::left)<<"---------- "<<setw(8)<<i<<"lines have written ----------"<<endl;
		
		//��1�У�ԭ2����Э������
		StrTemp = intToString(int((*RecdIter)->iProtocolType));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��2�У�ԭ3������������
		StrTemp = intToString(int((*RecdIter)->iService));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();	
		
		//��3�У�ԭ4����״̬��־
		StrTemp = intToString(int((*RecdIter)->iStatusFlag));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();			
		
		//��4�У�ԭ5����Դ��Ŀ���ֽ���
		StrTemp = intToString((*RecdIter)->iSrcBytes);
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��5�У�ԭ6����Ŀ�ĵ�Դ�ֽ���
		StrTemp = intToString((*RecdIter)->iDestBytes);
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��6�У�ԭ11������¼ʧ�ܴ���
		StrTemp = intToString((*RecdIter)->iFailedLogins);
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();		
		
		//��7�У�ԭ14�����Ƿ���root�û�Ȩ��
		StrTemp = intToString(int((*RecdIter)->bRootShell));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��8�У�ԭ16����root�û�Ȩ�޴�ȡ����
		StrTemp = intToString((*RecdIter)->iNumofRoot);
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();

		//��9�У�ԭ22�����Ƿ���guest�û���¼
		StrTemp = intToString(int((*RecdIter)->bGuestLogin));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();

		//��10�У�ԭ23����2����������ͬ������Ŀ
		StrTemp = intToString((*RecdIter)->iCount);
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();

		//��11�У�ԭ24����2����������ͬ�˿���Ŀ
		StrTemp = intToString((*RecdIter)->iSrvCount);
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��12�У�ԭ27����"REJ"���������������
		StrTemp = intToString(int((*RecdIter)->iRerrorRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��13�У�ԭ29�������ӵ���ͬ�˿�������
		StrTemp = intToString(int((*RecdIter)->iSameSrvRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��14�У�ԭ30�������ӵ���ͬ�˿�������
		StrTemp = intToString(int((*RecdIter)->iDiffSrvRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();

		//��15�У�ԭ33������ͬĿ�ĵ���ͬ�˿�������
		StrTemp = intToString((*RecdIter)->iDstHostSrvCount);
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��16�У�ԭ34������ͬĿ�ĵ���ͬ�˿�����������
		StrTemp = intToString(int((*RecdIter)->iDstHostSameSrvRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��17�У�ԭ35������ͬĿ�ĵز�ͬ�˿�����������
		StrTemp = intToString(int((*RecdIter)->iDstHostDiffSrvRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��18�У�ԭ36������ͬĿ�ĵ���ͬԴ�˿����ӱ���
		StrTemp = intToString(int((*RecdIter)->iDstHostSameSrcPortRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��19�У�ԭ37������ͬ����������ͬ�˿ڱ���
		StrTemp = intToString(int((*RecdIter)->iDstHostSrvDiffHostRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();
		
		//��20�У�ԭ39�������ӵ�ǰ������S0����ı���
		StrTemp = intToString(int((*RecdIter)->iDstHostSrvSerrorRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();		

		//��21�У�ԭ42�������ͱ�ǩ ��Ϊ5��
		StrTemp = intToString(int((*RecdIter)->iLabel));
		StrRecord += StrTemp;
		//StrRecord += ",";
		//cout<<"Record: "<<StrRecord<<endl;
		StrTemp.clear();		
    
    StrRecord += "\n";
    //cout<<"Record: "<<StrRecord<<endl;
    
    //����¼д��Ԥ��������ļ���
    fputs(StrRecord.c_str(),pOutFile);
    
		//��StrRecord�ַ������
		StrRecord.clear();		
	}
	
	//�ļ���ȡ��ϣ���ʾ��¼��	
	cout<<"All Records have written !"<<endl;
}

