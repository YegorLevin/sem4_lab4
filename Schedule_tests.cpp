#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sem4_lab4/Schedule.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

		
	TEST_CLASS(tests)
	{
	public:
		TEST_METHOD(best_way_simple)
		{
			Schedule * testSchedule = new Schedule("input.txt");
			ListClass<string> * way = testSchedule->best_way("�����-���������", "������");
			Assert::IsTrue("�����-���������" == way->at(0));
			Assert::IsTrue("������" == way->at(1));
		}
		TEST_METHOD(best_way_hard)
		{
			Schedule * testSchedule = new Schedule("input.txt");
			ListClass<string> * way = testSchedule->best_way("�����-���������", "�����������");
			Assert::IsTrue("�����-���������" == way->at(0));
			Assert::IsTrue("������" == way->at(1));
			Assert::IsTrue("���������" == way->at(2));
			Assert::IsTrue("�����������" == way->at(3));
		}
		TEST_METHOD(no_way_to_town)
		{
			Schedule * testSchedule = new Schedule("input.txt");
			ListClass<string> * way = testSchedule->best_way("���������", "������");
			Assert::IsTrue(way == nullptr);
		}
		TEST_METHOD(no_input_file_exception)
		{
			Schedule * testSchedule;
			try
			{
				testSchedule = new Schedule("inpuut.txt");
			}
			catch (logic_error message)
			{
				Assert::AreEqual("No input file", message.what());
			}
		}
		
	};
