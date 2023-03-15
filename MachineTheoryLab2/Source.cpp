#include <iostream>
#include <fstream>
#include <bitset>

const int commandLength = 2;
const int operandLength = 64;
const int devision = 0b11;
const int multiplication = 0b00;

int main()
{
	std::ifstream reader("file.txt");
	std::string input((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
	reader.close();
	int pointer = 0;
	if (input.size() != commandLength + operandLength * 2)
	{
		std::cout << "Incorrect length" << std::endl;
		return -1;
	}		
	std::string commandStr = std::string(&input[pointer], &input[pointer] + commandLength);
	pointer += commandLength;
	std::string operand1Str = std::string(&input[pointer], &input[pointer] + operandLength);
	pointer += operandLength;
	std::string operand2Str = std::string(&input[pointer], &input[pointer] + operandLength);
	if (commandStr.find_first_not_of("01") != std::string::npos)
	{
		std::cout << "Incorrect operation code" << std::endl;
		return -1;
	}	
	else if (operand1Str.find_first_not_of("01") != std::string::npos || operand2Str.find_first_not_of("01") != std::string::npos)
	{
		std::cout << "Incorrect input" << std::endl;
		return -1;
	}	
	int command = std::bitset<32>(commandStr).to_ulong();
	long long operand1 = std::bitset<64>(operand1Str).to_ullong();
	long long operand2 = std::bitset<64>(operand2Str).to_ullong();
	float result = 0;
	if (command == devision)
	{
		if (operand2 == 0)
		{
			std::cout << "Devision by zero" << std::endl;
			return -1;
		}
		result = operand1 / (float)operand2;
	}
	else if (command == multiplication)
		result = operand1 * operand2;

	std::cout << result << std::endl;	
}