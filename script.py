import subprocess
import unittest

class Colors:
	RESET = "\033[0m"
	RED = "\033[31m"
	GREEN = "\033[32m"
	YELLOW = "\033[33m"

def run_c_program(input_data):
	process = subprocess.run(input_data, text=True, capture_output=True)
	return process.stdout, process.stderr

class TestCProgram(unittest.TestCase):

	def test0(self):
		input_data, input_err = run_c_program(["bash", "-c", "touch f2; ./pipex f2 ls ls out; cat out; rm f2 out"])
		expected_output, expected_err = run_c_program(["bash", "-c", "touch f2; <f2 ls | ls >out; cat out; rm f2 out"])
		self.assertEqual(input_data, expected_output)
		self.assertEqual(input_err, expected_err)

	def test1(self):
		input_data, input_err = run_c_program(["bash", "-c", "./pipex Makefile cat cat out; cat out; rm out"])
		expected_output, expected_err = run_c_program(["bash", "-c", "<Makefile cat | cat >out; cat out; rm out"])
		self.assertEqual(input_data, expected_output)
		self.assertEqual(input_err, expected_err)

class CustomTestResult(unittest.TextTestResult):
	def __init__(self, *args, **kwargs):
		super().__init__(*args, **kwargs)
		self.tests_run = []

	def addSuccess(self, test):
		super().addSuccess(test)
		self.tests_run.append((test, "Passed"))

	def addFailure(self, test, err):
		super().addFailure(test, err)
		self.tests_run.append((test, "Failed"))

	def addError(self, test, err):
		super().addError(test, err)
		self.tests_run.append((test, "Error"))

class CustomTextTestRunner(unittest.TextTestRunner):
	def __init__(self, *args, **kwargs):
		super().__init__(*args, **kwargs)
		self.stream = open('/dev/null', 'w')

	def run(self, test):
		result = CustomTestResult(self.stream, self.descriptions, self.verbosity)
		test(result)
		for test, status in result.tests_run:
			# Extracting the method name without class and module information
			test_name = test._testMethodName
			Color = Colors.GREEN
			if status == "Error" or status == "Failed":
				Color = Colors.RED
			elif status == "Failed":
				Color = Colors.RED
			print(f"{test_name} - {Color}{status}{Colors.RESET}")
		return result

if __name__ == "__main__":
	unittest.main(testRunner=CustomTextTestRunner())
