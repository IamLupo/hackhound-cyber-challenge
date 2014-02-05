#include <boost/thread.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>

using namespace std;

enum Secret_Message
{
	MSG_DEC_SUCCES,
	MSG_ENC_SUCCES,
	MSG_USAGE,
	MSG_ERROR_INPUT_FILE,
	MSG_ERROR_OUTPUT_FILE,
	MSG_ERROR_FILE_FORMAT,
	MSG_ERROR_PASSWORD,
	MSG_ERROR_MALFUNCTION
};

enum Thread_Status
{
	THREAD_STATUS_NONE = -1,
	THREAD_STATUS_RUNNING,
	THREAD_STATUS_FINISHED
};

//Functions
unsigned int ThreadReverseMultiplication(int threads, unsigned int output, unsigned int mul);
void FindMasterThree(Thread_Status* thread_status, unsigned int begin, unsigned int end,
					unsigned int master_key[4], unsigned int enc_file_keys_3, unsigned int time);

char secret_message_0[] = { 0x4C, 0x77, 0x21, 0x26, 0x53, 0x50, 0x7C, 0x23, 0x25, 0x7A, 0x60,
							0x51, 0x27, 0x21, 0x21, 0x77, 0x77, 0x4C, 0x77, 0x4C, 0x00 };
char secret_message_1[] = { 0x77, 0x7A, 0x21, 0x26, 0x53, 0x50, 0x7C, 0x23, 0x25, 0x7A, 0x60,
							0x51, 0x27, 0x21, 0x21, 0x77, 0x77, 0x4C, 0x77, 0x4C, 0x00 }; 
char secret_message_2[] = { 0x27, 0x51, 0x4B, 0x4D, 0x77, 0x3E, 0x60, 0x21, 0x26, 0x53, 0x50,
							0x7C, 0x60, 0x0F, 0x49, 0x4C, 0x65, 0x77, 0x1F, 0x60, 0x49, 0x22,
							0x23, 0x24, 0x77, 0x75, 0x23, 0x7A, 0x1F, 0x60, 0x49, 0x22, 0x23,
							0x24, 0x77, 0x75, 0x25, 0x27, 0x7C, 0x1F, 0x60, 0x49, 0x50, 0x4B,
							0x51, 0x51, 0x7D, 0x25, 0x26, 0x4C, 0x1F, 0x00 };		
char secret_message_3[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x21, 0x4B, 0x7A, 0x60,
							0x7A, 0x25, 0x7C, 0x60, 0x25, 0x50, 0x77, 0x7A, 0x60, 0x23, 0x7A,
							0x50, 0x27, 0x7C, 0x60, 0x22, 0x23, 0x24, 0x77, 0x00 };
char secret_message_4[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x21, 0x4B, 0x7A, 0x60,
							0x7A, 0x25, 0x7C, 0x60, 0x25, 0x50, 0x77, 0x7A, 0x60, 0x25, 0x27,
							0x7C, 0x50, 0x27, 0x7C, 0x60, 0x22, 0x23, 0x24, 0x77, 0x00 };
char secret_message_5[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x23, 0x7A, 0x52, 0x4B,
							0x24, 0x23, 0x4C, 0x60, 0x22, 0x23, 0x24, 0x77, 0x60, 0x22, 0x25,
							0x26, 0x4F, 0x4B, 0x7C, 0x00 };
char secret_message_6[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x23, 0x7A, 0x21, 0x25,
							0x26, 0x26, 0x77, 0x21, 0x7C, 0x60, 0x50, 0x4B, 0x51, 0x51, 0x7D,
							0x25, 0x26, 0x4C, 0x00 };
char secret_message_7[] = { 0x77, 0x26, 0x26, 0x25, 0x26, 0x3E, 0x60, 0x51, 0x25, 0x4F, 0x77,
							0x7C, 0x78, 0x23, 0x7A, 0x4D, 0x60, 0x21, 0x4B, 0x27, 0x51, 0x77,
							0x4C, 0x60, 0x7C, 0x78, 0x77, 0x60, 0x4B, 0x50, 0x50, 0x24, 0x23,
							0x21, 0x4B, 0x7C, 0x23, 0x25, 0x7A, 0x60, 0x7C, 0x25, 0x60, 0x4F,
							0x4B, 0x24, 0x22, 0x27, 0x7A, 0x21, 0x7C, 0x23, 0x25, 0x7A, 0x00 };
char secret_message_8[] = { 0x1C, 0x26, 0x25, 0x24, 0x25, 0x24, 0x25, 0x24, 0x25, 0x00 };

void DecryptMessage(char* message)
{
	unsigned int message_length = (unsigned)strlen(message);
	
	int i;
	for (i = 0; i < message_length; i++)
	{
		message[i] = (message[i] * 3) & 0x8000007F;
	}
}

void ShowMessageAndExit(Secret_Message id)
{
	char* message_ptr;
	
	if(id == MSG_DEC_SUCCES)
		message_ptr = secret_message_0;
	else if(id == MSG_ENC_SUCCES)
		message_ptr = secret_message_1;
	else if(id == MSG_USAGE)
		message_ptr = secret_message_2;
	else if(id == MSG_ERROR_INPUT_FILE)
		message_ptr = secret_message_3;
	else if(id == MSG_ERROR_OUTPUT_FILE)
		message_ptr = secret_message_4;
	else if(id == MSG_ERROR_FILE_FORMAT)
		message_ptr = secret_message_5;
	else if(id == MSG_ERROR_PASSWORD)
		message_ptr = secret_message_6;
	else if(id == MSG_ERROR_MALFUNCTION)
		message_ptr = secret_message_7;
	
	//Decrypt
	DecryptMessage(message_ptr);
	
	//Draw
	printf("%s \n", message_ptr);
	
	//Exit
	if(id == MSG_DEC_SUCCES || id == MSG_ENC_SUCCES || id == MSG_USAGE)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
	/* You already know the answer! :D */
}

void InitKey(unsigned int generated_key[4], char* _password)
{
	unsigned int i, temp_value;
	
	temp_value = 0x3C;
	
	for(i = 0; i < 16; i++)
	{
		unsigned int byte_id = i / 4;
		unsigned int byte_position = i % 4;

		if(byte_position == 0)
			generated_key[byte_id] += (temp_value);
		else if(byte_position == 1)
			generated_key[byte_id] += (temp_value * 0x100);
		else if(byte_position == 2)
			generated_key[byte_id] += (temp_value * 0x10000);
		else if(byte_position == 3)
			generated_key[byte_id] += (temp_value * 0x1000000);
	}
	
	//Password
	unsigned int password_length = strlen(_password);
	unsigned int fix = 0x0;

	temp_value = (((generated_key[0] & 0xFF000000) / 0x1000000) + password_length) & 0xFF;
	generated_key[0] = (temp_value * 0x1000000) + (generated_key[0] & 0x00FFFFFF);
	
	for(i = 0; i < password_length + fix; i++)
	{
		unsigned int byte_id = ((i + 1) % 16) / 4;
		unsigned int byte_position = ((i + 1) % 16) % 4;
		
		if(byte_position == 0 && byte_id == 0)
		{
			fix += 0x1;
		}
		else if(byte_position == 0)
		{
			temp_value = (generated_key[byte_id] & 0xFF000000) / 0x1000000;
			temp_value = (temp_value + (unsigned int)_password[i - fix]) & 0xFF;
			generated_key[byte_id] = (temp_value * 0x1000000) + (generated_key[byte_id] & 0x00FFFFFF);
		}
		else if(byte_position == 1)
		{
			temp_value = (generated_key[byte_id] & 0xFF0000) / 0x10000;
			temp_value = (temp_value + (unsigned int)_password[i - fix]) & 0xFF;
			generated_key[byte_id] = (temp_value * 0x10000) + (generated_key[byte_id] & 0xFF00FFFF);
		}
		else if(byte_position == 2)
		{
			temp_value = (generated_key[byte_id] & 0xFF00) / 0x100;
			temp_value = (temp_value + (unsigned int)_password[i - fix]) & 0xFF;
			generated_key[byte_id] = (temp_value * 0x100) + (generated_key[byte_id] & 0xFFFF00FF);
		}
		else if(byte_position == 3)
		{
			temp_value = generated_key[byte_id] & 0xFF;
			temp_value = (temp_value + (unsigned int)_password[i - fix]) & 0xFF;
			/* You like carrot? */
			generated_key[byte_id] = temp_value + (generated_key[byte_id] & 0xFFFFFF00);
		}
	}
}

void GenerateKey(unsigned int master_key[4], unsigned int generated_key[4])
{
	unsigned int key_values[] = {	0xE,	//	0000	1110
									0x3,	//	0001	0011
									0xA,	//	0010	1010
									0xB,	//	0011	1011
									0x0,	//	0100	0000
									0x9,	//	0101	1001
									0x8,	//	0110	1000
									0x5,	//	0111	0101
									0xC,	//	1000	1100
									0xF,	//	1001	1111
									0x6,	//	1010	0110
									0x1,	//	1011	0001
									0x4,	//	1100	0100
									0xD,	//	1101	1101
									0x2,	//	1110	0010
									0x7 };	//	1111	0111 //4e byte doesnt change! :D hehe :D
	
	unsigned int i;
	unsigned int j;
	
	for (i = 0; i < 32; i++)
	{
		generated_key[0] = (generated_key[0] + master_key[0]) * 0xF97CE7B7;
		generated_key[1] = (generated_key[1] + master_key[1]) * 0xE9701ECB;
		generated_key[2] = (generated_key[2] + master_key[2]) * 0x70103AA1;
		generated_key[3] = (generated_key[3] + master_key[i % 3] + i) * 0xBD810313;

		unsigned int temp_key[] = 	{ 0x0, 0x0, 0x0, 0x0 };
		
		for(j = 0; j < 32; j++)
		{
			unsigned int id;
			id = (((generated_key[3] >> (0x1F - j)) & 0x1) * 0x2);
			id = (id ^ (generated_key[2] >> (0x1F - j)) & 0x1) * 0x2;
			id = (id ^ ((generated_key[1] >> (0x1F - j)) & 0x1)) * 0x2;
			id = id ^ ((generated_key[0] >> (0x1F - j)) & 0x1);

			temp_key[0] = (key_values[id] & 0x1) ^ (temp_key[0] + temp_key[0]); // Because the first bit never change the generate_key will also not change :D
			temp_key[1] = ((key_values[id] >> 0x1) & 0x1) ^ (temp_key[1] + temp_key[1]);
			temp_key[2] = ((key_values[id] >> 0x2) & 0x1) ^ (temp_key[2] + temp_key[2]);
			temp_key[3] = ((key_values[id] >> 0x3) & 0x1) ^ (temp_key[3] + temp_key[3]);
		}
		
		generated_key[0] = temp_key[0];
		generated_key[1] = temp_key[1];
		generated_key[2] = temp_key[2];
		generated_key[3] = temp_key[3];
	}
	
	generated_key[0] += master_key[0];
	generated_key[1] += master_key[1];
	generated_key[2] += master_key[2];
	generated_key[3] += master_key[0];
}

void InitMasterKey(unsigned int master_key[4], unsigned int generated_key[4])
{
	master_key[0] = generated_key[0];
	master_key[1] = generated_key[1];
	master_key[2] = generated_key[2];
	master_key[3] = generated_key[3];
	
	generated_key[0] = master_key[2] ^ master_key[1] ^ master_key[0];
	generated_key[1] = master_key[3] ^ master_key[1] ^ master_key[0];
	generated_key[2] = master_key[3] ^ master_key[2] ^ master_key[0];
	generated_key[3] = master_key[3] ^ master_key[2] ^ master_key[1];
}

/* Blub */

void InitMasterTimeKey(unsigned int master_key[4], unsigned int mastertime_key[4], unsigned int time)
{
	mastertime_key[0] = master_key[0] ^ time;
	mastertime_key[1] = master_key[1] ^ time;
	mastertime_key[2] = master_key[2] ^ time;
	mastertime_key[3] = master_key[3] ^ time;
	
	GenerateKey(master_key, mastertime_key);
}

void Encrypt(char* _input_file, char* _output_file, char* _password)
{
	FILE* input_file;
	FILE* output_file;

	size_t result;
	
	//Open Input File
	input_file = fopen(_input_file,"rb");
	if(input_file == NULL)
		ShowMessageAndExit(MSG_ERROR_INPUT_FILE);
	
	//Create Output File
	output_file = fopen(_output_file,"wb");
	if(output_file == NULL)
	{
		fclose(input_file);
		ShowMessageAndExit(MSG_ERROR_OUTPUT_FILE);
	}
	
	//Make Header
	char header[4] = { 'E', 'N', 'C', '/' };
	fwrite(header, sizeof(char), 4, output_file);
	
	//generate password hash and write to file
	unsigned int generated_key[4]	= { 0x0, 0x0, 0x0, 0x0 };
	unsigned int master_key[4]		= { 0x0, 0x0, 0x0, 0x0 };
	
	InitKey(generated_key, _password);
	GenerateKey(master_key, generated_key);
	InitMasterKey(master_key, generated_key);
	GenerateKey(master_key, generated_key);
	
	char password_hash[4] = {	((generated_key[0] & 0xFF) / 0x1),
								((generated_key[0] & 0xFF00) / 0x100),
								((generated_key[0] & 0xFF0000) / 0x10000),
								((generated_key[0] & 0xFF000000) / 0x1000000)};
	
	fwrite(password_hash, sizeof(char), 4, output_file);

	unsigned int time = GetTickCount();
	InitMasterTimeKey(master_key, generated_key, time); //WTF WHY?!
	
	char key[4];
	for(int i = 0; i < 4; i++)
	{
		char key[4] = {	((generated_key[i] & 0xFF) / 0x1),
						((generated_key[i] & 0xFF00) / 0x100),
						((generated_key[i] & 0xFF0000) / 0x10000),
						((generated_key[i] & 0xFF000000) / 0x1000000)};
		fwrite(key, sizeof(char), 4, output_file);
	}
	
	//read data and encrypt it
	char buffer[16];
	do
	{
		GenerateKey(master_key, generated_key);
		result = fread(buffer, 1, 16, input_file);
		
		buffer[0] = (buffer[0] & 0xFF) ^ (generated_key[0] & 0xFF); // HOP
		buffer[1] = (buffer[1] & 0xFF) ^ ((generated_key[0] & 0xFF00) / 0x100); // HOP
		buffer[2] = (buffer[2] & 0xFF) ^ ((generated_key[0] & 0xFF0000) / 0x10000); // HOP
		buffer[3] = (buffer[3] & 0xFF) ^ ((generated_key[0] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[4] = (buffer[4] & 0xFF) ^ (generated_key[1] & 0xFF); // HOP
		buffer[5] = (buffer[5] & 0xFF) ^ ((generated_key[1] & 0xFF00) / 0x100); // HOP
		buffer[6] = (buffer[6] & 0xFF) ^ ((generated_key[1] & 0xFF0000) / 0x10000); // HOP
		buffer[7] = (buffer[7] & 0xFF) ^ ((generated_key[1] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[8] = (buffer[8] & 0xFF) ^ (generated_key[2] & 0xFF); // HOP
		buffer[9] = (buffer[9] & 0xFF) ^ ((generated_key[2] & 0xFF00) / 0x100); // HOP
		buffer[10] = (buffer[10] & 0xFF) ^ ((generated_key[2] & 0xFF0000) / 0x10000); // HOP
		buffer[11] = (buffer[11] & 0xFF) ^ ((generated_key[2] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[12] = (buffer[12] & 0xFF) ^ (generated_key[3] & 0xFF); // HOP
		buffer[13] = (buffer[13] & 0xFF) ^ ((generated_key[3] & 0xFF00) / 0x100); // HOP
		buffer[14] = (buffer[14] & 0xFF) ^ ((generated_key[3] & 0xFF0000) / 0x10000); // HOP
		buffer[15] = (buffer[15] & 0xFF) ^ ((generated_key[3] & 0xFF000000) / 0x1000000); // HOP
		
		fwrite(buffer, sizeof(char), result, output_file);
	}
	while(result == 16);
	
	fclose(input_file);
	fclose(output_file);
	
	ShowMessageAndExit(MSG_ENC_SUCCES);
}

void Decrypt(char* _input_file, char* _output_file, char* _password)
{
	FILE* input_file;
	FILE* output_file;

	size_t result;
	
	//Open Input File
	input_file = fopen(_input_file,"rb");
	if(input_file == NULL)
		ShowMessageAndExit(MSG_ERROR_INPUT_FILE);
	
	//Create Output File
	output_file = fopen(_output_file,"wb");
	if(output_file == NULL)
	{
		fclose(input_file);
		ShowMessageAndExit(MSG_ERROR_OUTPUT_FILE);
	}
	
	//Read Format
	char header[4];
	result = fread(header, 1, 4, input_file);
	
	if(result != 4)
	{
		fclose(input_file);
		fclose(output_file);
		ShowMessageAndExit(MSG_ERROR_MALFUNCTION);
	}
	
	if(header[0] == 0x2F && header[1] == 0x43 && header[2] == 0x4E && header[3] == 0x45 ) // header is "ENC/"
	{
		fclose(input_file);
		fclose(output_file);
		ShowMessageAndExit(MSG_ERROR_FILE_FORMAT);
	}
	
	//generate password hash with password
	unsigned int generated_key[4]	= { 0x0, 0x0, 0x0, 0x0 };
	unsigned int master_key[4]		= { 0x0, 0x0, 0x0, 0x0 };
	
	InitKey(generated_key, _password);
	GenerateKey(master_key, generated_key);
	InitMasterKey(master_key, generated_key);
	GenerateKey(master_key, generated_key);
	
	//Get password hash out of file
	char password_hash[4];
	result = fread(password_hash, 1, 4, input_file);
	
	if(result != 4)
	{
		fclose(input_file);
		fclose(output_file);
		ShowMessageAndExit(MSG_ERROR_MALFUNCTION);
	}
	//Check Password hash with each other
	if(	(password_hash[0] & 0xFF) != ((generated_key[0] & 0xFF) / 0x1) ||
				(password_hash[1] & 0xFF) != ((generated_key[0] & 0xFF00) / 0x100) ||
				(password_hash[2] & 0xFF) != ((generated_key[0] & 0xFF0000) / 0x10000) ||
				(password_hash[3] & 0xFF) != ((generated_key[0] & 0xFF000000) / 0x1000000))
	{
		fclose(input_file);
		fclose(output_file);
		/* I told you so! */
		ShowMessageAndExit(MSG_ERROR_PASSWORD);
	}
	
	//Get generated_key out of file
	char key[4];
	for(int i = 0; i < 4; i++)
	{
		result = fread(key, 1, 4, input_file);
		
		if(result != 4)
		{
			fclose(input_file);
			fclose(output_file);
			ShowMessageAndExit(MSG_ERROR_MALFUNCTION);
		}
		generated_key[i] = ((key[3] & 0xFF) * 0x1000000) + ((key[2] & 0xFF) * 0x10000) + ((key[1] & 0xFF) * 0x100) + (key[0] & 0xFF);
	}
	
	//read data and decrypt it
	char buffer[16];
	do
	{
		GenerateKey(master_key, generated_key);
		result = fread(buffer, 1, 16, input_file);
		
		buffer[0] = (buffer[0] & 0xFF) ^ (generated_key[0] & 0xFF); // HOP
		buffer[1] = (buffer[1] & 0xFF) ^ ((generated_key[0] & 0xFF00) / 0x100); // HOP
		buffer[2] = (buffer[2] & 0xFF) ^ ((generated_key[0] & 0xFF0000) / 0x10000); // HOP
		buffer[3] = (buffer[3] & 0xFF) ^ ((generated_key[0] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[4] = (buffer[4] & 0xFF) ^ (generated_key[1] & 0xFF); // HOP
		buffer[5] = (buffer[5] & 0xFF) ^ ((generated_key[1] & 0xFF00) / 0x100); // HOP
		buffer[6] = (buffer[6] & 0xFF) ^ ((generated_key[1] & 0xFF0000) / 0x10000); // HOP
		buffer[7] = (buffer[7] & 0xFF) ^ ((generated_key[1] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[8] = (buffer[8] & 0xFF) ^ (generated_key[2] & 0xFF); // HOP
		buffer[9] = (buffer[9] & 0xFF) ^ ((generated_key[2] & 0xFF00) / 0x100); // HOP
		buffer[10] = (buffer[10] & 0xFF) ^ ((generated_key[2] & 0xFF0000) / 0x10000); // HOP
		buffer[11] = (buffer[11] & 0xFF) ^ ((generated_key[2] & 0xFF000000) / 0x1000000); // HOP
		
		buffer[12] = (buffer[12] & 0xFF) ^ (generated_key[3] & 0xFF); // HOP
		buffer[13] = (buffer[13] & 0xFF) ^ ((generated_key[3] & 0xFF00) / 0x100); // HOP
		buffer[14] = (buffer[14] & 0xFF) ^ ((generated_key[3] & 0xFF0000) / 0x10000); // HOP
		buffer[15] = (buffer[15] & 0xFF) ^ ((generated_key[3] & 0xFF000000) / 0x1000000); // HOP
		
		fwrite(buffer, sizeof(char), result, output_file);
	}
	while(result == 16);
	
	fclose(input_file);
	fclose(output_file);
	
	ShowMessageAndExit(MSG_DEC_SUCCES);
}


//---- Reverse Functions ----
void ReverseBites(unsigned int key[4])
{
	unsigned int key_values[] = {	0x4,	//x
									0xB,	//x
									0xE,	//x
									0x1,	//x
									0xC,	//x
									0x7,	//x
									0xA,	//x
									0xF,	//x
									0x6,	//x
									0x5,	//x
									0x2,	//x
									0x3,	//x
									0x8,	//x
									0xD,	//x
									0x0,	//
									0x9 };	//
	
	unsigned int id;
	unsigned int i;
	unsigned int temp_key[] = 	{ 0x0, 0x0, 0x0, 0x0 };
		
	for(i = 0; i < 32; i++)
	{
		id = (((key[3] >> (0x1F - i)) & 0x1) * 0x2);
		id = (id ^ (key[2] >> (0x1F - i)) & 0x1) * 0x2;
		id = (id ^ ((key[1] >> (0x1F - i)) & 0x1)) * 0x2;
		id = id ^ ((key[0] >> (0x1F - i)) & 0x1);
		
		//temp_key[3] = (key_values[id] & 0x1) ^ (temp_key[3] + temp_key[3]); //fail ! This we can make better :D
		temp_key[0] = ((key[0] >> (0x1F - i)) & 0x1) ^ (temp_key[0] + temp_key[0]); // Fix
		temp_key[1] = ((key_values[id] >> 0x1) & 0x1) ^ (temp_key[1] + temp_key[1]);
		temp_key[2] = ((key_values[id] >> 0x2) & 0x1) ^ (temp_key[2] + temp_key[2]);
		temp_key[3] = ((key_values[id] >> 0x3) & 0x1) ^ (temp_key[3] + temp_key[3]);
	}
	
	key[0] = temp_key[0];
	key[1] = temp_key[1];
	key[2] = temp_key[2];
	key[3] = temp_key[3];
}

void ReverseMultiplication(unsigned int* return_value, Thread_Status* thread_status, unsigned int begin, unsigned int end, unsigned int output, unsigned int mul)
{
	try
	{
		unsigned int i;
		for(i = begin; i < end; i++)
		{
			if((i * mul) == output)
			{
				*thread_status = THREAD_STATUS_FINISHED;
				*return_value = i;
				
				return;
			}
		}
	}
	catch(boost::thread_interrupted&)
	{
		return;
	}
}

void ReverseGenerateKey(int threads, unsigned int master_key[4], unsigned int password_edited[4])
{
	password_edited[0] = master_key[0];
	password_edited[1] = master_key[1];
	password_edited[2] = master_key[2];
	password_edited[3] = master_key[3];
	
	unsigned int i;
	unsigned int j;
	unsigned int id;
	for(i = 0; i < 32; i++)
	{
		id = (31 - i);
		ReverseBites(password_edited);

		//Multiply
		password_edited[0] = ThreadReverseMultiplication(threads, password_edited[0], 0xF97CE7B7);
		password_edited[1] = ThreadReverseMultiplication(threads, password_edited[1], 0xE9701ECB);
		password_edited[2] = ThreadReverseMultiplication(threads, password_edited[2], 0x70103AA1);
		password_edited[3] = ThreadReverseMultiplication(threads, password_edited[3], 0xBD810313) - id;
	}
	
	char password[15];
	password[0] = (((password_edited[0] & 0xFF00) / 0x100) - 0x3C) & 0xFF;
	password[1] = ((password_edited[0] & 0xFF) - 0x3C) & 0xFF;
	password[2] = (((password_edited[1] & 0xFF000000) / 0x1000000) - 0x3C) & 0xFF;
	password[3] = (((password_edited[1] & 0xFF0000) / 0x10000) - 0x3C) & 0xFF;
	password[4] = (((password_edited[1] & 0xFF00) / 0x100) - 0x3C) & 0xFF;
	password[5] = ((password_edited[1] & 0xFF) - 0x3C) & 0xFF;
	password[6] = (((password_edited[2] & 0xFF000000) / 0x1000000) - 0x3C) & 0xFF;
	password[7] = (((password_edited[2] & 0xFF0000) / 0x10000) - 0x3C) & 0xFF;
	password[8] = (((password_edited[2] & 0xFF00) / 0x100) - 0x3C) & 0xFF;
	password[9] = ((password_edited[2] & 0xFF) - 0x3C) & 0xFF;
	password[10] = (((password_edited[3] & 0xFF000000) / 0x1000000) - 0x3C) & 0xFF;
	password[11] = (((password_edited[3] & 0xFF0000) / 0x10000) - 0x3C) & 0xFF;
	password[12] = (((password_edited[3] & 0xFF00) / 0x100) - 0x3C) & 0xFF;
	password[13] = ((password_edited[3] & 0xFF) - 0x3C) & 0xFF;
	password[14] = '\0';
	
	cout << master_key[3] << " - " << ((((password_edited[0] & 0xFF0000) / 0x10000) - 0x3C) & 0xFF) << " - " << password << endl;
}

//---- Threads ----
unsigned int ThreadReverseMultiplication(int threads, unsigned int output, unsigned int mul)
{
	unsigned int i;
	boost::thread_group tgroup;
	unsigned int return_value[threads];
	Thread_Status thread_status[threads];
	
	unsigned int space = 0xFFFFFFFF / threads;
	
	for(i = 0; i < threads; i++)
	{
		return_value[i] = 0;
		thread_status[i] = THREAD_STATUS_RUNNING;
		
		tgroup.create_thread(
			boost::bind(
				&ReverseMultiplication,
				&return_value[i],
				&thread_status[i],
				i * space,
				(i + 1) * space,
				output,
				mul
			)
		);
	}

	bool found = false;
	unsigned int id = 0;
	while(!found)
	{
		for(i = 0; i < threads; i++)
		{
			if(thread_status[i] == THREAD_STATUS_FINISHED)
			{
				thread_status[i] = THREAD_STATUS_NONE;
				
				if(return_value[i] != 0)
				{
					found = true;
					id = i;
				}
			}
		}
	}
	
	//Ending threads
	tgroup.interrupt_all();
	tgroup.join_all();
	
	return return_value[id];
}

void FindMasterThree(Thread_Status* thread_status, unsigned int begin, unsigned int end,
					unsigned int master_key[4], unsigned int enc_file_keys_3, unsigned int time)
{
	try
	{
		unsigned int i;
		unsigned int mastertime_key[4] = { 0x0, 0x0, 0x0, 0x0 };
		
		for(i = begin; i < end; i++)
		{
			master_key[3] = i;
			
			InitMasterTimeKey(master_key, mastertime_key, time);
			
			if(mastertime_key[3] == enc_file_keys_3)
			{
				cout << "found = " << i << endl;
			}
		}
		
		*thread_status = THREAD_STATUS_FINISHED;
		return;
	}
	catch(boost::thread_interrupted&)
	{
		return;
	}
}

//---- Cracker ----

//Part 1
/*
	We know that a zip begins with "0x50, 0x4b, 0x03, 0x04". Also we know the encrypted data. We can calculated the next encryption key.
	Next we know that GenerateKey function has a bug.
	generated_key_0_output = (generated_key_0_input * master_key_0) * 0xF97CE7B7 <- 32 times repeated.
	Now we have this case:
	generated_key_output = next_encryption_key
	generated_key_0_input = 0xe4d6f212;
	We now only have to bruteforce the master_key_0
*/
unsigned int Crack_Part_1(unsigned int enc_file_keys_0, unsigned int enc_file_data_0)
{
	unsigned int generate;
	unsigned int master;
	
	unsigned int check_0 = 0x50 ^ (enc_file_data_0 & 0xFF);							//Key part 1
	unsigned int check_1 = 0x4b ^ ((enc_file_data_0 & 0xFF00) / 0x100);				//Key part 2
	unsigned int check_2 = 0x03 ^ ((enc_file_data_0 & 0xFF0000) / 0x10000);			//Key part 3
	unsigned int check_3 = 0x04 ^ ((enc_file_data_0 & 0xFF000000) / 0x1000000);		//Key part 4
	
	unsigned int check_key = (check_3 * 0x1000000) + (check_2 * 0x10000) + (check_1 * 0x100) + check_0;
	
	unsigned int i;
	for(i = 0x4293777F; i < 0xFFFFFFFF; i++)
	{
		generate = enc_file_keys_0;
		master = i;
		
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;
		generate *= 0xF97CE7B7;
		generate += master;

		if(generate == check_key)
			return i;
	}
	
	return 0;
}

//Part 2
/*
	Now we have the master_key_0 we can now bruteforce the time
*/
unsigned int Crack_Part_2(unsigned int master_key_0, unsigned int enc_file_keys_0)
{
	unsigned int generate;
	
	unsigned int i;
	for(i = 0xE1C871; i < 0xFFFFFFFF; i++)
	{
		generate = master_key_0 ^ i;
		
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		
		if(enc_file_keys_0 == generate)
			return i;
	}
	return 0;
}

//Part 3
/*
	Because we have the master_key_0 and the enc_file_passwordhash we can try to find the generator_0
*/
unsigned int Crack_Part_3(unsigned int master_key_0, unsigned int enc_file_passwordhash)
{
	unsigned int generate;
	
	unsigned int i;
	for(i = 0x72EE2D82; i < 0xFFFFFFFF; i++)
	{
		generate = i;
		
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		generate *= 0xF97CE7B7;
		generate += master_key_0;
		
		if(enc_file_passwordhash == generate)
			return i;
	}
	return 0;
}

/*
	Because we know that "master_key_1XORmaster_key_2 = master_key_1 ^ master_key_2". We know that there are only 2^32 posibilities to bruteforce.
	Also master_key_3 is useless in GenerateKey because it hasnt been used.
*/
void Crack_Part_4(unsigned int master_key[4], unsigned int enc_file_keys[4], unsigned int enc_file_data_1, unsigned int master_key_1XORmaster_key_2, unsigned int options[10])
{
	unsigned int found = 0x0;
	
	unsigned int check_0 = 0x14 ^ (enc_file_data_1 & 0xFF);							//Key part 1
	unsigned int check_1 = 0x00 ^ ((enc_file_data_1 & 0xFF00) / 0x100);				//Key part 2
	unsigned int check_2 = 0x00 ^ ((enc_file_data_1 & 0xFF0000) / 0x10000);			//Key part 3
	unsigned int check_3 = 0x00 ^ ((enc_file_data_1 & 0xFF000000) / 0x1000000);		//Key part 4
	unsigned int check_key = (check_3 * 0x1000000) + (check_2 * 0x10000) + (check_1 * 0x100) + check_0;
	
	unsigned int i;
	for(i = 0x1DD79212; i < 0x1DD79213; i++) // Right answer
	{
		unsigned int generate[] = { enc_file_keys[0], enc_file_keys[1], enc_file_keys[2], enc_file_keys[3] };
		unsigned int master[] = { master_key[0], i, (i ^ master_key_1XORmaster_key_2), 0 };
		
		GenerateKey(master, generate);
		
		if(generate[1] == check_key)
		{
			options[found] = i;
			
			found++;
		}
	}
}

//Part 5
/*
Because we only don't know the master_key_3 we need to bruteforce to get the same values as "enc_file_keys".
*/
void Crack_Part_5(int threads, unsigned int master_key[4], unsigned int enc_file_keys_3, unsigned int time)
{
	unsigned int i;
	boost::thread_group tgroup;
	Thread_Status thread_status[threads];
	unsigned int space = 0xFFFFFFFF / threads;
	
	for(i = 0; i < threads; i++)
	{
		unsigned int temp_master_key[4] = { master_key[0], master_key[1], master_key[2], 0x0 };
		
		thread_status[i] = THREAD_STATUS_RUNNING;
		
		tgroup.create_thread(
			boost::bind(
				&FindMasterThree,
				&thread_status[i],
				i * space,
				(i + 1) * space,
				temp_master_key,
				enc_file_keys_3,
				time
			)
		);
	}

	unsigned int done = 0;
	bool found = false;
	while(!found)
	{
		for(i = 0; i < threads; i++)
		{
			if(thread_status[i] == THREAD_STATUS_FINISHED)
			{
				thread_status[i] = THREAD_STATUS_NONE;
				done++;
				cout << "done = " << done << endl;
				if(done >= threads)
					found = true;
			}
		}
	}
	
	//Ending threads
	tgroup.interrupt_all();
	tgroup.join_all();
}

//Part 6
/*
Because we have the generate and the master_key complete, we can reverse the "GenerateKey" function to get
the output of "InitKey" function. What we know that the first value - 3C is the length. Also if the password is longer then
15 symbols it will add 2 charter with each other. like the 1e and the 16e charter + 3C. In this case our password is 16 charters.
We have to look with our eyes what the 1e and 16e charter will be.
*/
void Crack_Part_6(int threads, unsigned int master_key[4], unsigned int password_edited[4])
{
	unsigned int i;
	unsigned int options[43] = {
								0x023B6A2D,	0x04F502B4,	0x065D6A2D,	0x0C7502B4,
								0x0E5D6A2D,	0x125D6A2D,	0x1A06A22D,	0x2306A22D,
								0x28116A2D,	0x2B7B6A2D,	0x2C116A2D,	0x2E5D6A2D,
								0x3A3B6A2D,	0x3E86A22D,	0x48F502B4,	0x4C7502B4,
								0x525D6A2D,	0x5ADD6A2D,	0x637D6A2D,	0x6D9D6A2D,
								0x6E5D6A2D,	0x7E86A22D,	0x823B6A2D,	0x865D6A2D,
								0x8E5D6A2D,	0x925D6A2D,	0x965D6A2D,	0x9A06A22D,
								0xA8116A2D,	0xA8F502B4,	0xAE5D6A2D,	0xBA3B6A2D,
								0xC37D6A2D,	0xC686A22D,	0xC8F502B4,	0xDA06A22D,
								0xE25D6A2D,	0xE37D6A2D,	0xE8116A2D,	0xED9D6A2D,
								0xF25D6A2D,	0xFA3B6A2D,	0xFE86A22D
								};
	
	for (i = 0; i < 43; i++)
	{
		master_key[3] = options[i];
		ReverseGenerateKey(threads, master_key, password_edited);
	}
}

//---- Main ----
int main(int argc, char* argv[])
{
	if(argc == 5 && strcmp(argv[1], "-e") == 0)
	{
		Encrypt(argv[2], argv[3], argv[4]);
	}
	else if(argc == 5 && strcmp(argv[1], "-d") == 0)
	{
		Decrypt(argv[2], argv[3], argv[4]);
	}
	else if(argc == 3 && strcmp(argv[1], "-c") == 0)
	{
		int threads = static_cast<int>(boost::thread::hardware_concurrency());
		
		//Known values
		unsigned int enc_file_passwordhash	= 0xb0a0da81;
		unsigned int enc_file_keys[]		= { 0xac9b280d, 0x753012f2, 0xa700d292, 0x64017b35 };
		unsigned int enc_file_data[]		= { 0xbc7d475c, 0x4843623c, 0xe61aa83c, 0x6248ea14 };
		
		unsigned int generated_key[4]				= { 0x0,	0x0,	0x0,	0x0 };
		unsigned int password_edited[4]				= { 0x0, 0x0, 0x0, 0x0 };
		unsigned int master_key_1XORmaster_key_2	= 0x0;
		unsigned int mastertime_key[4]				= { 0x0,	0x0,	0x0,	0x0 };
		
		//Bruteforced values
		unsigned int master_key[4]			= { 0x4293777F, 0x1DD79212, 0x2DAAC8EF, 0x965D6A2D };
		unsigned int enc_file_time			= 0x00E1C871;
		
		if(strcmp(argv[2], "master") == 0)
		{
			//Master key 0
			master_key[0] = Crack_Part_1(enc_file_keys[0], enc_file_data[0]);
			cout << "master_key_0 = " << master_key[0] << endl;
			
			//Encryption Time
			enc_file_time = Crack_Part_2(master_key[0], enc_file_keys[0]);
			cout << "enc_file_time = " << enc_file_time << endl;
			
			//Generator 0
			generated_key[0] = Crack_Part_3(master_key[0], enc_file_passwordhash);
			master_key_1XORmaster_key_2 = generated_key[0] ^ master_key[0];
			cout << "generated_key = " << generated_key[0] << endl;
			cout << "master_key_1XORmaster_key_2 = " << master_key_1XORmaster_key_2 << endl;
			
			//Master key 1 & 2
			unsigned int options[10] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
			Crack_Part_4(master_key, enc_file_keys, enc_file_data[1], master_key_1XORmaster_key_2, options);
				
			//Draw
			cout << "Options" << endl;
			unsigned int i;
			for(i = 0; i < 10 && options[i] != 0; i++)
			{
				cout << "master_key =	"	<< master_key[0] << " - " << options[i] << " - " << (options[i] ^ master_key_1XORmaster_key_2) << endl;
			}
		}
		else if(strcmp(argv[2], "full_master") == 0) // Look at the keys.txt for the output
		{
			Crack_Part_5(threads, master_key, enc_file_keys[3], enc_file_time);
		}
		else if(strcmp(argv[2], "password") == 0) // Look at the keys.txt for the output
		{
			Crack_Part_6(threads, master_key, password_edited);
		}
		/*
		Result:
		4C B7 7C 7F - A7 84 6C 91 - AA 80 70 91 - 7C AA 80 A9
		-----------------------------------------------------
		   48 40 43 - 6b 48 30 55 - 6e 44 34 55 - 40 6e 44 6d
		   33
		charters = 0xC4 - 0xC3 = 0x10 = 16 charters
		Pass: H@CkH0UnD4U@nDm3
		*/
	}
	else
	{
		ShowMessageAndExit(MSG_USAGE);
	}
}
