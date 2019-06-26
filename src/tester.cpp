#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <fstream>
#include "tester.h"
#include "colormode.h"

/**
 * @brief
 * Constructor of Tester class.
 * @param testCaseNumber The number of tests going to use.
 */
Tester::Tester(int testCaseNumber)
{
	for(int i = 1; i <= testCaseNumber; i++)
		importTestCase(i);
}

/**
 * @brief
 * Function for importing a testcase from the input file.
 * @param testCaseNumber 
 * The number going to import. The testfile should be in ./testfiles and named 'input(testCaseNumber).txt'
 * sample input file is in ./testfiles/sample.txt.
 */
void Tester::importTestCase(int testCaseNumber)
{
	std::ifstream inFile("./testfiles/input" + std::to_string(testCaseNumber) + ".txt");
	std::string line;
	TestCase testCase;
	std::vector<Action> solution;
	int answerNumbers;

	if(!inFile)
	{
		std::cout << "Testcase #" << testCaseNumber << " file not exists... Plz check your ./testfiles folder" << std::endl;
		exit(1);
	}

	try 
	{
		inFile >> answerNumbers;
		for(int i = 0; i < answerNumbers; i++)
		{
			Action newAction;
			inFile >> newAction.x >> newAction.y >> newAction.dir;
			solution.push_back(newAction);
		}

		for(int i = 1; i <= 6; i++)
			for(int j = 1; j <= 6; j++)
				inFile >> testCase.board[i][j];

		solutions.push_back(solution);
		testCases.push_back(testCase);
	}
	catch(...)
	{
		std::cout << "Testcase #" << testCaseNumber << " has wrong format... Plz check your file in ./testfiles folder" << std::endl;
		exit(1);
	}
}

/**
 * @brief
 * Test all the testcases that you put in the testfiles folder.
 */
void Tester::testAll()
{
	int correctTestCases = 0, result;
	std::string message;
	Color::Modifier red(Color::FG_RED);
	Color::Modifier blue(Color::FG_BLUE);
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);

	std::cout << "\n***Start Testing!***" << std::endl << std::endl;

	for(int t = 0; t < testCases.size(); t++)
	{
		std::cout << "[TC #";
		if(t + 1 < 10) std::cout << "0";
		std::cout << t + 1 << "] ";
		result = test(t);

		switch(result)
		{
			case 0:
				correctTestCases++;
				std::cout << green;
				message = "CORRECT!";
				break;
			case 1:
				std::cout << red;
				message = "WRONG ANSWER";
				break;
			case 2:
				std::cout << red;
				message = "TIME LIMIT";
				break;
			default:
				message = "System Error... Plz contact to the developer";
		}

		std::cout << message << def << std::endl;
	}

	std::cout << "\nTotal Result: " << correctTestCases << " / " << testCases.size() << std::endl;
	if(correctTestCases == testCases.size())
	{
		std::cout << green << "\nCongratulations! You're now an alpha beta pruning master!" << def << std::endl;
	}
}

int Tester::scoring(TestCase testCase)
{
	int sc[3] = {0, 0, 0}, num[3] = {0, 0, 0};
	
	for(int i = 1; i <= 5; ++i)
	{
		num[1] = num[2] = 0;
		for(int j = 1; j <= 5; ++j)
		{
			num[testCase.board[i][j]]++;
		}
		
		for(int k = 1; k <= 2; ++k)
		{
			if(num[k] == 5) 
				sc[k] = 1e9;
			else 
				sc[k] += num[k] * num[k];
			num[k] = 0;
		}
		
		
		for(int j = 1; j <= 5; ++j)
		{
			num[testCase.board[j][i]]++;
		}

		for(int k = 1; k <= 2; ++k)
		{
			if(num[k] == 5) 
				sc[k] = 1e9;
			else 
				sc[k] += num[k] * num[k];
			num[k] = 0;
		}
	}
	
	for(int j = 1; j <= 5; ++j)
	{
		num[testCase.board[j][j]]++;
	}

	for(int k = 1; k <= 2; ++k)
	{
		if(num[k] == 5) 
			sc[k] = 1e9;
		else 
			sc[k] += num[k] * num[k];
		num[k] = 0;
	}
	
	for(int j = 1; j <= 5; ++j)
	{
		num[testCase.board[j][6 - j]]++;
	}

	for(int k = 1; k <= 2; ++k)
	{
		if(num[k] == 5) 
			sc[k]=1e9;
		else 
			sc[k] += num[k] * num[k];
		num[k] = 0;
	}
	
	if(sc[1] - sc[2] > 1e8) 
		return 1e9;
	else if(sc[1] - sc[2] < -1e8) 
		return -1e9;
	else 
		return sc[1] - sc[2];	
}

/**
 * @brief
 * Return the result of a test.
 * @param testCaseNumber The number of testcase you are going to test.
 * @return 
 * If correct answer, returns 0 and wrong answer, returns 1. 
 * If time limit exceeds, returns 1.
 */
int Tester::test(int testCaseNumber)
{
	bool flag = false;
	std::mutex m;
	std::condition_variable cv;

	TestCase testCase = testCases[testCaseNumber];
	std::vector<Action> solution = solutions[testCaseNumber];
	Action userAnswer = {0, 0, 0};

	std::thread t([&]()
	{
		solve(testCase, userAnswer);
		flag = true;
		cv.notify_one();
	});

	t.detach();

	{
		std::unique_lock<std::mutex> l(m);

		if(!cv.wait_for(l, std::chrono::seconds(1), [&flag]{ return flag; }))
			return 2;
	}

	for(Action& ans : solution)
	{
		if(ans == userAnswer)
			return 0;
	}

	return 1;
}
