#include <iostream>
#include <fstream>
#include <bitset>

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

int main()
{
	std::ifstream reader("file.txt");
	std::string input((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
	int error = Error::NO_ERRORS;
	reader.close();
	int pointer = 0;

	if (input.size() != commandLength + operandLength * 2)
		error = Error::INCORRECT_OPERAND_LENGTH;

	std::string commandStr = std::string(&input[pointer], &input[pointer] + commandLength);
	pointer += commandLength;
	std::string operand1Str = std::string(&input[pointer], &input[pointer] + operandLength);
	pointer += operandLength;
	std::string operand2Str = std::string(&input[pointer], &input[pointer] + operandLength);

	if (commandStr.find_first_not_of("01") != std::string::npos)
		error = Error::INCORRECT_OPCODE;

	else if (operand1Str.find_first_not_of("01") != std::string::npos || operand2Str.find_first_not_of("01") != std::string::npos)
		error = Error::INCORRECT_INPUT;	

	int command = std::bitset<32>(commandStr).to_ulong();
	unsigned long long operand1 = std::bitset<64>(operand1Str).to_ullong();
	unsigned long long operand2 = std::bitset<64>(operand2Str).to_ullong();
	int result = 0;

	if (command == devision && operand2 == 0)
		error = Error::DIVISION_BY_ZERO;

	if (operand1 > ~(unsigned long long)0 / operand2)
		error = Error::GRID_OVERFLOW;

	if (error == Error::NO_ERRORS)
	{
		result = command == devision ? operand1 / operand2 : operand1 * operand2;
		std::cout << std::bitset<64>(result).to_string() << std::endl;
	}
}