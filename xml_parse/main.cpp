//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "tinyxml2.h"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;



#define SWITCH_5152_MAX_PORT	10
#define GATE_RULE_MAX			50		// this value should not exceed 16,here set to 50 only to adjust the current xml file
#define QUEUE_SIZE				8
#define SWITCH_NUM				2

#define SWITCH_INDEX_A	0
#define SWITCH_INDEX_B	1

typedef enum
{
	SWITCH_PORT_0 = 0,
	SWITCH_PORT_1,
	SWITCH_PORT_2,
	SWITCH_PORT_3,
	SWITCH_PORT_4,
	SWITCH_PORT_5,
	SWITCH_PORT_6,
	SWITCH_PORT_7,
	SWITCH_PORT_8,
	SWITCH_PORT_9,
}SWITCH_PORT;

typedef struct
{
	uint8 traffic_class;
	uint16 queue_sdu_size;
}Queue_Sdu_St;

typedef struct
{
	uint8 gate_state;
	uint32 time_interval;
}Gate_Ctrl_Entry_St;
typedef struct
{
	uint8 Port_Index;// 
	Queue_Sdu_St queue_sdu_data[SWITCH_5152_MAX_PORT][QUEUE_SIZE];
	Gate_Ctrl_Entry_St gate_Entry[SWITCH_5152_MAX_PORT][GATE_RULE_MAX];
	uint32 Port_CycleTime[SWITCH_5152_MAX_PORT];
}Gata_Para_Cfg_St;

 
using namespace std;
using namespace tinyxml2;



class PARSE_XML
{
private:
	uint8 Interface_Num;
	Gata_Para_Cfg_St gate_para_data;
public:
	PARSE_XML();
	~PARSE_XML();
	void DecodeXML(uint8 index);
	uint8 GetInterface_Num() const { return Interface_Num; }
	uint8 GetUsedEntryNumber(uint8 port) const;
	uint32 GetPortCycleTime(uint8 port) const;
	uint8 GetGateState_PerPort(uint8 port, uint8 entry_index) const;
	uint32 GetGateTimeInterval_PerPort(uint8 port, uint8 entry_index) const;
};

void create_switch_cfg_file(FILE* output_file_ptr, PARSE_XML& switch_a_xml, PARSE_XML& switch_b_xml);

int main(int argv, char* argc[])
{
	FILE* fp = NULL;
	PARSE_XML parse_xml;
	PARSE_XML parse_xml_B;
	
	
	fp = fopen("./output/switch_cfg.c", "r+");
	if (fp != NULL)
	{
		parse_xml.DecodeXML(SWITCH_INDEX_A);
		parse_xml_B.DecodeXML(SWITCH_INDEX_B);
		create_switch_cfg_file(fp, parse_xml, parse_xml_B);
		fclose(fp);
	}
	return 0;
}


void create_switch_cfg_file(FILE* output_file_ptr, PARSE_XML& switch_a_xml, PARSE_XML& switch_b_xml)
{
	fprintf(output_file_ptr,"/*this code generated from YANG module xml file*/ \n");
	fprintf(output_file_ptr, "/*g-pulse all rights reserved*/ \n");
	fprintf(output_file_ptr, "typedef struct \n");
	fprintf(output_file_ptr, "{\n");
	fprintf(output_file_ptr, "\tunsigned char %s;\n", "GateState");
	fprintf(output_file_ptr, "\tunsigned long %s;\n", "TimeInterval");
	fprintf(output_file_ptr, "}Gate_Entry_St;\n");
	fprintf(output_file_ptr, "\n");// 

	fprintf(output_file_ptr, "#define GP_88Q5152_CONST_FAR_DATA_START \n");
	fprintf(output_file_ptr, "#include \"Gp_88Q5152_MemMap.h\" \n");
	fprintf(output_file_ptr, "\n");// 


	fprintf(output_file_ptr, "#define SWITCH_A_PORT0_CLASS_0\n");
	fprintf(output_file_ptr, "#define SWITCH_A_PORT0_CLASS_1\n");
	fprintf(output_file_ptr, "#define SWITCH_A_PORT0_CLASS_2\n");
	fprintf(output_file_ptr, "#define SWITCH_A_PORT0_CLASS_3\n");
	fprintf(output_file_ptr, "#define SWITCH_A_PORT0_CLASS_4\n");
	fprintf(output_file_ptr, "#define SWITCH_A_PORT0_CLASS_5\n");
	fprintf(output_file_ptr, "#define SWITCH_A_PORT0_CLASS_6\n");
	fprintf(output_file_ptr, "#define SWITCH_A_PORT0_CLASS_7\n");
	
	fprintf(output_file_ptr, "\n");// 
	uint8 switch_a_port1_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_1);
	uint8 switch_a_port2_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_2);
	uint8 switch_a_port3_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_3);
	uint8 switch_a_port4_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_4);
	uint8 switch_a_port5_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_5);
	uint8 switch_a_port6_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_6);
	uint8 switch_a_port7_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_7);
	uint8 switch_a_port8_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_8);
	uint8 switch_a_port9_gate_entry = switch_a_xml.GetUsedEntryNumber(SWITCH_PORT_9);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT1_MAX_ENTRY\t%d\n", switch_a_port1_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT2_MAX_ENTRY\t%d\n", switch_a_port2_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT3_MAX_ENTRY\t%d\n", switch_a_port3_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT4_MAX_ENTRY\t%d\n", switch_a_port4_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT5_MAX_ENTRY\t%d\n", switch_a_port5_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT6_MAX_ENTRY\t%d\n", switch_a_port6_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT7_MAX_ENTRY\t%d\n", switch_a_port7_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT8_MAX_ENTRY\t%d\n", switch_a_port8_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_A_PORT9_MAX_ENTRY\t%d\n", switch_a_port9_gate_entry);
	fprintf(output_file_ptr, "\n");//

	uint32 switch_a_Port1_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_1);
	uint32 switch_a_Port2_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_2);
	uint32 switch_a_Port3_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_3);
	uint32 switch_a_Port4_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_4);
	uint32 switch_a_Port5_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_5);
	uint32 switch_a_Port6_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_6);
	uint32 switch_a_Port7_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_7);
	uint32 switch_a_Port8_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_8);
	uint32 switch_a_Port9_PeriodTime = switch_a_xml.GetPortCycleTime(SWITCH_PORT_9);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P1_PeriodTime = %ld\n", switch_a_Port1_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P2_PeriodTime = %ld\n", switch_a_Port2_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P3_PeriodTime = %ld\n", switch_a_Port3_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P4_PeriodTime = %ld\n", switch_a_Port4_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P5_PeriodTime = %ld\n", switch_a_Port5_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P6_PeriodTime = %ld\n", switch_a_Port6_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P7_PeriodTime = %ld\n", switch_a_Port7_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P8_PeriodTime = %ld\n", switch_a_Port8_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_A_P9_PeriodTime = %ld\n", switch_a_Port9_PeriodTime);

	fprintf(output_file_ptr, "\n");//

	/*******************************************************************************************************/
	uint8 gate_state;
	uint32 gate_time_Slot;
	uint8 switch_port_index = 0;
	uint8 switch_Ports_Entry_Collect[SWITCH_5152_MAX_PORT];
	switch_Ports_Entry_Collect[SWITCH_PORT_1] = switch_a_port1_gate_entry;
	switch_Ports_Entry_Collect[SWITCH_PORT_2] = switch_a_port2_gate_entry;
	switch_Ports_Entry_Collect[SWITCH_PORT_3] = switch_a_port3_gate_entry;
	switch_Ports_Entry_Collect[SWITCH_PORT_4] = switch_a_port4_gate_entry;
	switch_Ports_Entry_Collect[SWITCH_PORT_5] = switch_a_port5_gate_entry;
	switch_Ports_Entry_Collect[SWITCH_PORT_6] = switch_a_port6_gate_entry;
	switch_Ports_Entry_Collect[SWITCH_PORT_7] = switch_a_port7_gate_entry;
	switch_Ports_Entry_Collect[SWITCH_PORT_8] = switch_a_port8_gate_entry;
	switch_Ports_Entry_Collect[SWITCH_PORT_9] = switch_a_port9_gate_entry;
	for (switch_port_index = SWITCH_PORT_1; switch_port_index < SWITCH_5152_MAX_PORT; switch_port_index++)
	{
		if (switch_Ports_Entry_Collect[switch_port_index] > 0)
		{
			if (switch_port_index == SWITCH_PORT_1) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P1_Gate[SWITCH_A_PORT1_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_2) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P2_Gate[SWITCH_A_PORT2_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_3) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P3_Gate[SWITCH_A_PORT3_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_4) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P4_Gate[SWITCH_A_PORT4_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_5) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P5_Gate[SWITCH_A_PORT5_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_6) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P6_Gate[SWITCH_A_PORT6_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_7) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P7_Gate[SWITCH_A_PORT7_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_8) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P8_Gate[SWITCH_A_PORT8_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_9) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_A_P9_Gate[SWITCH_A_PORT9_MAX_ENTRY] = \n");
			fprintf(output_file_ptr, "{\n");
			for (uint8 i = 0; i < switch_Ports_Entry_Collect[switch_port_index]; i++)
			{
				gate_state = switch_a_xml.GetGateState_PerPort(switch_port_index, i);
				gate_time_Slot = switch_a_xml.GetGateTimeInterval_PerPort(switch_port_index, i);
				fprintf(output_file_ptr, "\t{0x%x,", gate_state);
				fprintf(output_file_ptr, "0x%lx},\n", gate_time_Slot);
			}
			fprintf(output_file_ptr, "};\n");
		}
	}
	/**************************************************************************************************************************************/
	fprintf(output_file_ptr, "#define SWITCH_B_PORT0_CLASS_0\n");
	fprintf(output_file_ptr, "#define SWITCH_B_PORT0_CLASS_1\n");
	fprintf(output_file_ptr, "#define SWITCH_B_PORT0_CLASS_2\n");
	fprintf(output_file_ptr, "#define SWITCH_B_PORT0_CLASS_3\n");
	fprintf(output_file_ptr, "#define SWITCH_B_PORT0_CLASS_4\n");
	fprintf(output_file_ptr, "#define SWITCH_B_PORT0_CLASS_5\n");
	fprintf(output_file_ptr, "#define SWITCH_B_PORT0_CLASS_6\n");
	fprintf(output_file_ptr, "#define SWITCH_B_PORT0_CLASS_7\n");

	fprintf(output_file_ptr, "\n");// 
	uint8 switch_b_port1_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_1);
	uint8 switch_b_port2_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_2);
	uint8 switch_b_port3_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_3);
	uint8 switch_b_port4_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_4);
	uint8 switch_b_port5_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_5);
	uint8 switch_b_port6_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_6);
	uint8 switch_b_port7_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_7);
	uint8 switch_b_port8_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_8);
	uint8 switch_b_port9_gate_entry = switch_b_xml.GetUsedEntryNumber(SWITCH_PORT_9);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT1_MAX_ENTRY\t%d\n", switch_b_port1_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT2_MAX_ENTRY\t%d\n", switch_b_port2_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT3_MAX_ENTRY\t%d\n", switch_b_port3_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT4_MAX_ENTRY\t%d\n", switch_b_port4_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT5_MAX_ENTRY\t%d\n", switch_b_port5_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT6_MAX_ENTRY\t%d\n", switch_b_port6_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT7_MAX_ENTRY\t%d\n", switch_b_port7_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT8_MAX_ENTRY\t%d\n", switch_b_port8_gate_entry);
	fprintf(output_file_ptr, "#define SWITCH_B_PORT9_MAX_ENTRY\t%d\n", switch_b_port9_gate_entry);
	fprintf(output_file_ptr, "\n");//

	uint32 switch_b_Port1_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_1);
	uint32 switch_b_Port2_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_2);
	uint32 switch_b_Port3_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_3);
	uint32 switch_b_Port4_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_4);
	uint32 switch_b_Port5_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_5);
	uint32 switch_b_Port6_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_6);
	uint32 switch_b_Port7_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_7);
	uint32 switch_b_Port8_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_8);
	uint32 switch_b_Port9_PeriodTime = switch_b_xml.GetPortCycleTime(SWITCH_PORT_9);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P1_PeriodTime = %ld\n", switch_b_Port1_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P2_PeriodTime = %ld\n", switch_b_Port2_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P3_PeriodTime = %ld\n", switch_b_Port3_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P4_PeriodTime = %ld\n", switch_b_Port4_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P5_PeriodTime = %ld\n", switch_b_Port5_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P6_PeriodTime = %ld\n", switch_b_Port6_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P7_PeriodTime = %ld\n", switch_b_Port7_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P8_PeriodTime = %ld\n", switch_b_Port8_PeriodTime);
	fprintf(output_file_ptr, "const unsigned long SWITCH_B_P9_PeriodTime = %ld\n", switch_b_Port9_PeriodTime);

	fprintf(output_file_ptr, "\n");//
	/*******************************************************************************************************/
	switch_Ports_Entry_Collect[1] = switch_b_port1_gate_entry;
	switch_Ports_Entry_Collect[2] = switch_b_port2_gate_entry;
	switch_Ports_Entry_Collect[3] = switch_b_port3_gate_entry;
	switch_Ports_Entry_Collect[4] = switch_b_port4_gate_entry;
	switch_Ports_Entry_Collect[5] = switch_b_port5_gate_entry;
	switch_Ports_Entry_Collect[6] = switch_b_port6_gate_entry;
	switch_Ports_Entry_Collect[7] = switch_b_port7_gate_entry;
	switch_Ports_Entry_Collect[8] = switch_b_port8_gate_entry;
	switch_Ports_Entry_Collect[9] = switch_b_port9_gate_entry;

	for (switch_port_index = SWITCH_PORT_1; switch_port_index < SWITCH_5152_MAX_PORT; switch_port_index++)
	{
		if (switch_Ports_Entry_Collect[switch_port_index] > 0)
		{
			if (switch_port_index == SWITCH_PORT_1) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P1_Gate[SWITCH_B_PORT1_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_2) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P2_Gate[SWITCH_B_PORT2_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_3) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P3_Gate[SWITCH_B_PORT3_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_4) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P4_Gate[SWITCH_B_PORT4_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_5) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P5_Gate[SWITCH_B_PORT5_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_6) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P6_Gate[SWITCH_B_PORT6_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_7) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P7_Gate[SWITCH_B_PORT7_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_8) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P8_Gate[SWITCH_B_PORT8_MAX_ENTRY] = \n");
			if (switch_port_index == SWITCH_PORT_9) fprintf(output_file_ptr, "const Gate_Entry_St SWITCH_B_P9_Gate[SWITCH_B_PORT9_MAX_ENTRY] = \n");
			fprintf(output_file_ptr, "{\n");
			for (uint8 i = 0; i < switch_Ports_Entry_Collect[switch_port_index]; i++)
			{
				gate_state = switch_b_xml.GetGateState_PerPort(switch_port_index, i);
				gate_time_Slot = switch_b_xml.GetGateTimeInterval_PerPort(switch_port_index, i);
				fprintf(output_file_ptr, "\t{0x%x,", gate_state);
				fprintf(output_file_ptr, "0x%lx},\n", gate_time_Slot);
			}
			fprintf(output_file_ptr, "};\n");
		}
	}

	/*******************************************************************************************************/
	fprintf(output_file_ptr, "#define GP_88Q5152_CONST_FAR_DATA_STOP \n");
	fprintf(output_file_ptr, "#include \"Gp_88Q5152_MemMap.h\" \n");
	fprintf(output_file_ptr, "\n");// 
}


PARSE_XML::PARSE_XML()
{
	Interface_Num = 0;
	int i, j;
	for(i = 0; i < SWITCH_5152_MAX_PORT; i++)
	{
		for (j = 0; j < QUEUE_SIZE; j++)
		{
			gate_para_data.queue_sdu_data[i][j].traffic_class = 0;
			gate_para_data.queue_sdu_data[i][j].queue_sdu_size = 0;
		}
	}
	for (i = 0; i < SWITCH_5152_MAX_PORT; i++)
	{
		for (j = 0; j < GATE_RULE_MAX; j++)
		{
			gate_para_data.gate_Entry[i][j].gate_state = 0;
			gate_para_data.gate_Entry[i][j].time_interval = 0;
		}
	}
	for (i = 0; i < SWITCH_5152_MAX_PORT; i++)
	{
		gate_para_data.Port_CycleTime[i] = 0;
	}
}

PARSE_XML::~PARSE_XML()
{
}


uint8 PARSE_XML::GetUsedEntryNumber(uint8 port) const
{
	uint8 cnt = 0;
	uint8 i;
	for (i = 0; i < GATE_RULE_MAX; i++)
	{
		if ((gate_para_data.gate_Entry[port][i].gate_state == 0) && (gate_para_data.gate_Entry[port][i].time_interval == 0))
		{
			cnt = i;
			break;
		}
	}
	return cnt;
}

uint32 PARSE_XML::GetPortCycleTime(uint8 port) const
{
	uint32 cycle_time = 0;
	cycle_time = gate_para_data.Port_CycleTime[port];
	return cycle_time;
}

uint8 PARSE_XML::GetGateState_PerPort(uint8 port, uint8 entry_index) const
{
	uint8 gate_state = 0;
	gate_state = gate_para_data.gate_Entry[port][entry_index].gate_state;
	return gate_state;
}

uint32 PARSE_XML::GetGateTimeInterval_PerPort(uint8 port, uint8 entry_index) const
{
	uint32 gate_time = 0;
	gate_time = gate_para_data.gate_Entry[port][entry_index].time_interval;
	return gate_time;
}
void PARSE_XML::DecodeXML(uint8 index)
{
	XMLDocument xml;
	//import xml file
	if (index == SWITCH_INDEX_A)
	{
		if (xml.LoadFile("./YANG/Interface_Switch3.xml") != XML_SUCCESS)
		{
			return;
		}
	}
	else if (index == SWITCH_INDEX_B)
	{
		if (xml.LoadFile("./YANG/Interface_Switch4.xml") != XML_SUCCESS)
		{
			return;
		}
	}
	else
	{
		return;
	}

	XMLElement* rootNode = xml.RootElement();
	if (rootNode == NULL)
	{
		return;
	}
	XMLElement* elmtInterface = rootNode->FirstChildElement("interface");
	//loop the interface for all switch Ports
	do
	{
		XMLElement* elmtInsName = elmtInterface->FirstChildElement("name");
		XMLElement* elmtInsEnable = elmtInterface->FirstChildElement("enabled");
		XMLElement* elmtInstype = elmtInterface->FirstChildElement("type");
		XMLElement* elmtInsGatePar = elmtInterface->FirstChildElement("bridge-port")->FirstChildElement("gate-parameter-table");
		XMLElement* elmtInsFramePreemptPar = elmtInterface->FirstChildElement("bridge-port")->FirstChildElement("frame-preemption-parameters");
		if (elmtInsName)
		{
			Interface_Num++;
			const char* InsNamePtr = elmtInsName->GetText();// get P1
			cout << "Switch Port is: " << InsNamePtr << endl;
			//compare the string type
			if (!strcmp(InsNamePtr, "P0"))
			{
				gate_para_data.Port_Index = 0x00;
			}
			else if (!strcmp(InsNamePtr, "P1"))
			{
				gate_para_data.Port_Index = 0x01;
			}
			else if (!strcmp(InsNamePtr, "P2"))
			{
				gate_para_data.Port_Index = 0x02;
			}
			else if (!strcmp(InsNamePtr, "P3"))
			{
				gate_para_data.Port_Index = 0x03;
			}
			else if (!strcmp(InsNamePtr, "P4"))
			{
				gate_para_data.Port_Index = 0x04;
			}
			else if (!strcmp(InsNamePtr, "P5"))
			{
				gate_para_data.Port_Index = 0x05;
			}
			else if (!strcmp(InsNamePtr, "P6"))
			{
				gate_para_data.Port_Index = 0x06;
			}
			else if (!strcmp(InsNamePtr, "P7"))
			{
				gate_para_data.Port_Index = 0x07;
			}
			else if (!strcmp(InsNamePtr, "P8"))
			{
				gate_para_data.Port_Index = 0x08;
			}
			else if (!strcmp(InsNamePtr, "P9"))
			{
				gate_para_data.Port_Index = 0x09;
			}
			else
			{
				cout << "Port cfg is not correct" << endl;
				return;
			}
			const char* InsEnablePtr = elmtInsEnable->GetText();
			cout << InsEnablePtr << endl;
			const char* InsType = elmtInstype->GetText();
			cout << InsType << endl;
			if (elmtInsGatePar)
			{
				//loop the queue-max-sdu-table
				XMLElement* elmtQueue_max_sdu_tbl = elmtInsGatePar->FirstChildElement("queue-max-sdu-table");
				do
				{
					if (elmtQueue_max_sdu_tbl)
					{
						
						XMLElement* QueueChild_traffic = elmtQueue_max_sdu_tbl->FirstChildElement("traffic-class");
						XMLElement* QueueChild_queue_sdu = elmtQueue_max_sdu_tbl->FirstChildElement("queue-max-sdu");
						uint8 traffic_class_local;
						if (QueueChild_traffic != NULL)
						{
							const char* traffic_class = QueueChild_traffic->GetText();
							cout << "traffic-class is: "<<traffic_class << endl;
							traffic_class_local = atoi(traffic_class);
							if (traffic_class_local < QUEUE_SIZE)
							{
								gate_para_data.queue_sdu_data[gate_para_data.Port_Index][traffic_class_local].traffic_class = traffic_class_local;
							}
							else
							{
								cout << "traffic class value error" << endl;
								return;
							}
						}
						else
						{
							cout << "no traffic-class element" << endl;
							break;
						}
						if (QueueChild_queue_sdu != NULL)
						{
							const char* queue_sdu = QueueChild_queue_sdu->GetText();
							cout << "queue-max-sdu is: " << queue_sdu << endl;
							uint16 queue_sdu_size_local = atoi(queue_sdu);
							gate_para_data.queue_sdu_data[gate_para_data.Port_Index][traffic_class_local].queue_sdu_size = queue_sdu_size_local;
						}
						else
						{
							cout << "no queue-max-sdu element" << endl;
							break;
						}
					}
					else
					{
						cout << "no queue-max-sdu-table element" << endl;
					}
					elmtQueue_max_sdu_tbl = elmtQueue_max_sdu_tbl->NextSiblingElement();//next queue-max-sdu-table
				} while (elmtQueue_max_sdu_tbl != NULL);
				//get gate-enabled

				XMLElement* elmtAdminCtrlList = elmtInsGatePar->FirstChildElement("admin-control-list");
				if (elmtAdminCtrlList)
				{
					// loop the time interval value
					XMLElement* elmtGateEntry = elmtAdminCtrlList->FirstChildElement("gate-control-entry");
					do
					{
						XMLElement* elmtGateEntryIndex = elmtGateEntry->FirstChildElement("index");
						if (elmtGateEntryIndex)
						{
							XMLElement* elmtGateEntryState = elmtGateEntry->FirstChildElement("gate-states-value");
							XMLElement* elmtGateEntryTimeInterval = elmtGateEntry->FirstChildElement("time-interval-value");
							const char* GateEntryIndex = elmtGateEntryIndex->GetText();
							const char* GateEntryState = elmtGateEntryState->GetText();
							const char* GateEntryTimeInterval = elmtGateEntryTimeInterval->GetText();

							cout << "Gate index is: " << GateEntryIndex << " and its gate state is: " << GateEntryState << " and its gate time interval is: " << GateEntryTimeInterval << endl;
							uint8 gate_entry_index_local = atoi(GateEntryIndex);
							uint8 gate_state_local = atoi(GateEntryState);
							uint32 gate_time_interval = atoi(GateEntryTimeInterval);
							gate_para_data.gate_Entry[gate_para_data.Port_Index][gate_entry_index_local].gate_state = gate_state_local;
							gate_para_data.gate_Entry[gate_para_data.Port_Index][gate_entry_index_local].time_interval = gate_time_interval;
						}
						else
						{
							break;
						}
						elmtGateEntry = elmtGateEntry->NextSiblingElement();
					} while (elmtGateEntry != NULL);
				}
				else
				{
					cout << "no admin-control-list" << endl;
				}
				//get cycle time
				XMLElement* elmtAdminCycleTime = elmtInsGatePar->FirstChildElement("admin-cycle-time")->FirstChildElement("numerator");
				if (elmtAdminCycleTime)
				{
					const char* AdminCycleTime = elmtAdminCycleTime->GetText();
					cout << "the cycle time of this port is: " << AdminCycleTime << endl;
					uint32 port_cycle_time = atoi(AdminCycleTime);
					gate_para_data.Port_CycleTime[gate_para_data.Port_Index] = port_cycle_time;
				}
			}
			if (elmtInsFramePreemptPar)
			{
				XMLElement* FramePreempTbl = elmtInsFramePreemptPar->FirstChildElement("frame-preemption-status-table");
				do
				{


					FramePreempTbl = FramePreempTbl->NextSiblingElement();
				} while (FramePreempTbl != NULL);
			}
			else
			{
				cout << "no frame-preemption-parameters" << endl;
			}
		}
		else
		{
			return;
		}
		elmtInterface = elmtInterface->NextSiblingElement();//next interface
	} while (elmtInterface != NULL);
}
