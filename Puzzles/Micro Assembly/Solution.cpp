#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Instruction
{
	std::string key;
	std::vector<std::string> arguments;
};

static bool IsNumber(const std::string& value)
{
	try
	{
		std::size_t pos;
		std::stoi(value, &pos);
		return pos == value.length();
	}
	catch (std::invalid_argument const &)
	{
		return false;
	}
	catch (std::out_of_range const &)
	{
		return false;
	}
}

static std::unordered_map<char, int32_t> ParseRegisters()
{
	std::unordered_map<char, int32_t> registers;

	std::cin >> registers['a'];
	std::cin >> registers['b'];
	std::cin >> registers['c'];
	std::cin >> registers['d'];
	std::cin.ignore();

	return registers;
}

static int32_t ParseInteger()
{
	int32_t value;
	std::cin >> value;
	std::cin.ignore();
	return value;
}

static Instruction ParseInstruction(const std::string& instructionLine)
{
	std::stringstream ss(instructionLine);

	Instruction instruction;

	std::string value;
	
	if (std::getline(ss, value, ' '))
	{
		instruction.key = value;
	}

	while (std::getline(ss, value, ' '))
	{
		if (!value.empty())
			instruction.arguments.push_back(value);
	}
	
	return instruction;
}

static void RunAssembly(std::unordered_map<char, int32_t>& registers, const std::vector<Instruction>& instructions)
{
	uint32_t instructionCount = instructions.size();
	uint32_t instructionIndex = 0;

	while (instructionIndex < instructionCount)
	{
		const Instruction& instruction = instructions.at(instructionIndex);

		if (instruction.key == "MOV")
		{
			const char dest = instruction.arguments.at(0)[0];
			const std::string src = instruction.arguments.at(1);

			if (IsNumber(src))  registers[dest] = std::stoi(src);
			else                registers[dest] = registers[src[0]];
		}
		else if (instruction.key == "ADD" || instruction.key == "SUB")
		{
			const char dest = instruction.arguments.at(0)[0];

			const std::string srcA = instruction.arguments.at(1);
			const int32_t valueA = IsNumber(srcA) ? std::stoi(srcA) : registers[srcA[0]]; 

			const std::string srcB = instruction.arguments.at(2);
			const int32_t valueB = IsNumber(srcB) ? std::stoi(srcB) : registers[srcB[0]];

			if (instruction.key == "ADD")   registers[dest] = valueA + valueB;
			else                            registers[dest] = valueA - valueB;
		}
		else if (instruction.key == "JNE")
		{
			const int32_t jumpIndex = std::stoi(instruction.arguments.at(0));

			const char srcA = instruction.arguments.at(1)[0];

			const std::string srcB = instruction.arguments.at(2);
			const int32_t valueB = IsNumber(srcB) ? std::stoi(srcB) : registers[srcB[0]];

			if (registers[srcA] != valueB)
			{
				instructionIndex = jumpIndex;
				continue;
			}
		}

		instructionIndex++;
	}
}

int main()
{
	// Create all registers
	std::unordered_map<char, int32_t> registers = ParseRegisters();

	// Parse and queue all instructions
	uint32_t instructionCount = ParseInteger();
	std::vector<Instruction> instructions;
	for (uint32_t i = 0; i < instructionCount; i++)
	{
		std::string instructionLine;
		std::getline(std::cin, instructionLine);

		instructions.push_back(ParseInstruction(instructionLine));
	}

	// Run the assembly
	RunAssembly(registers, instructions);

	// Return the result
	std::cout << registers.at('a') << " ";
	std::cout << registers.at('b') << " ";
	std::cout << registers.at('c') << " ";
	std::cout << registers.at('d') << "\n";
}