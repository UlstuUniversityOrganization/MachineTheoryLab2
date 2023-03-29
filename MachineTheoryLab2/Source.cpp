#include <iostream>
#include <fstream>
#include <bitset>
#include <string>

const int commandLength = 2;
const int operandLength = 64;
const int devision = 0b11;
const int multiplication = 0b00;

class Error
{
public:
	static const int NO_ERRORS = 0b000;
	static const int DIVISION_BY_ZERO = 0b001;
	static const int INCORRECT_OPCODE = 0b010;
	static const int INCORRECT_INPUT = 0b011;
	static const int INCORRECT_OPERAND_LENGTH = 0b100;
	static const int GRID_OVERFLOW = 0b101;
};

void report(int s, int code, unsigned long long op1, unsigned long long op2, unsigned long long rez, int err)
{
	std::cout << "s" << s << "(" << std::bitset<3>(s).to_string() << ")" << std::endl;
	std::cout << "kod = " << std::bitset<2>(code).to_string() << std::endl;
	std::cout << "Op1 = " << std::bitset<64>(op1).to_string() << std::endl;
	std::cout << "Op2 = " << std::bitset<64>(op2).to_string() << std::endl;
	std::cout << "Rez = " << std::bitset<64>(rez).to_string() << std::endl;
	std::cout << "Err = " << std::bitset<3>(err).to_string() << std::endl;
	std::cout << std::endl;
}

int command = 0;
unsigned long long operand1 = 0;
unsigned long long operand2 = 0;
int result = 0;
int error = Error::NO_ERRORS;

int main()
{
	report(0, command, operand1, operand2, result, error);
	std::ifstream reader("file.txt");
	std::string input((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
	reader.close();
	int pointer = 0;
	report(1, command, operand1, operand2, result, error);

	if (input.size() != commandLength + operandLength * 2)
		error = Error::INCORRECT_OPERAND_LENGTH;
	report(2, command, operand1, operand2, result, error);

	std::string commandStr = std::string(&input[pointer], &input[pointer] + commandLength);
	pointer += commandLength;
	std::string operand1Str = std::string(&input[pointer], &input[pointer] + operandLength);
	pointer += operandLength;
	std::string operand2Str = std::string(&input[pointer], &input[pointer] + operandLength);
	report(3, command, operand1, operand2, result, error);

	if (commandStr.find_first_not_of("01") != std::string::npos)
		error = Error::INCORRECT_OPCODE;
	else if (operand1Str.find_first_not_of("01") != std::string::npos || operand2Str.find_first_not_of("01") != std::string::npos)
		error = Error::INCORRECT_INPUT;	
	report(4, command, operand1, operand2, result, error);

	command = std::bitset<32>(commandStr).to_ulong();
	operand1 = std::bitset<64>(operand1Str).to_ullong();
	operand2 = std::bitset<64>(operand2Str).to_ullong();
	report(5, command, operand1, operand2, result, error);
	

	if (command == devision && operand2 == 0)
		error = Error::DIVISION_BY_ZERO;
	report(6, command, operand1, operand2, result, error);

	if (command == multiplication && operand1 > ~(unsigned long long)0 / operand2)
		error = Error::GRID_OVERFLOW;
	report(7, command, operand1, operand2, result, error);

	if (error == Error::NO_ERRORS)
		result = command == devision ? operand1 / operand2 : operand1 * operand2;
	report(0, command, operand1, operand2, result, error);
}