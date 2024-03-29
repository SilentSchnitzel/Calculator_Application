#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

//these have to be included before any class that uses the windows api.
//in fact that should be done for anything that does not use the winapi
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include "Global.h"
#include "Calculator_Screen.h"
#include "CalculatorApplication.h"
#include "History.h"
#include "Math.h"


using namespace rapidjson;
using namespace std;

Global g;

Calculator_Screen::Calculator_Screen()
{
	ifstream file;

	file.open("calculator_data.json");
	if (!file)
	{
		//Setting up the json file in information will be stored.
		Document document;
		document.SetObject();

		//Creating another document that will serve almost as a sub json.
		//sub json for the equation history
		Document EquationHistory;
		EquationHistory.SetObject();

		//sub json for answer history
		Document AnswerHistory;
		AnswerHistory.SetObject();

		document.AddMember("Current Equation", "", document.GetAllocator());
		document.AddMember("Current Answer", "", document.GetAllocator());
		document.AddMember("Equation History", EquationHistory, document.GetAllocator());
		document.AddMember("Answer History", AnswerHistory, document.GetAllocator());
		document.AddMember("Mode", "Light Mode", document.GetAllocator());

		// Serialize the JSON document to a file
		//hopefully this code will actually create the json file
		StringBuffer buf;
		PrettyWriter<StringBuffer> writer(buf);
		//this line of code converts or serializes document into a stream
		//a stream is simply an abstract representation of a sequence of data that can be read from or written to
		//this stream will allow the user
		//in other words this line of code seems to be an important step in creating the json file?
		document.Accept(writer);
		ofstream json_file("calculator_data.json"); //creates an output file stream object called json_file and opens a new file called data.json for writing?
		json_file << buf.GetString() << endl; //method is called to retrieve the serialized JSON data as a string. Finally, the serialized JSON data is written to the output file using <<
	}
	else
	{
		return;
	}
}

void Calculator_Screen::render_screen(HWND hwnd)
{
	stringstream ss;
	ifstream file("calculator_data.json");

	ss << file.rdbuf();
	string json_str = ss.str();

	Document doc;
	doc.Parse(json_str.c_str());
	string text = doc["Current Equation"].GetString();
	if (text.length() > 30)
	{
		MessageBox(hwnd, L"You have reached the maximum length for an equation", L"Error", 1);
		return;
	}
	
	// Create a new font
	LOGFONT lf = { 0 };
	lf.lfHeight = 10; // set font height to a certain amount of pixels
	lf.lfWeight = FW_NORMAL;
	lf.lfCharSet = DEFAULT_CHARSET;
	lstrcpy(lf.lfFaceName, TEXT("Arial"));
	HFONT hFont = CreateFontIndirect(&lf);
	
	
	//hdc means handle device context
	//it is a data structure that handles graphic objects and their associated attributes
	//get the hdc
	HDC hdc = GetDC(hwnd);

	SelectObject(hdc, hFont);

	LPCWSTR screen_message = g.convert_to_lpcwstr(text);

	//erase everything in a given rectangle by invalidating that rectance
	RECT rect;
	rect.left = 10;
	rect.top = 10;
	rect.right = 10000; 
	rect.bottom = 100;
	InvalidateRect(hwnd, &rect, TRUE);

	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	TextOut(hdc, 10, 35, screen_message, text.length());
	//cleanup
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
	ReleaseDC(hwnd, hdc);
}

void Calculator_Screen::update_json(string character, bool special_msg)
{
	//This is how the program will handle messages sent by the buttons when they are clicked
	//This will sort the message into two categories so that they can be correctly stored in the json
	stringstream ss;
	//convert the character to a c-styled string
	const char* msg = character.c_str();

	if (special_msg == false) 
	{
		// Read the JSON file into a string
		ifstream file("calculator_data.json");
		ss << file.rdbuf();
		string json_str = ss.str();

		//parse the json into a document object
		Document json;
		json.Parse(json_str.c_str());

		//find the value to update
		Value& equation_update = json["Current Equation"];

		// the size that the buffer should be
		size_t len = strlen(equation_update.GetString()) + strlen(msg) + 1;

		//allocate memory for the buffer based off of the length of the new string
		char* buffer = new char[len];
		strcpy(buffer, equation_update.GetString());
		strcat(buffer, msg);
		string new_msg = buffer;
		equation_update.SetString(new_msg.c_str(), new_msg.length(), json.GetAllocator());
		//deallocate that memory to avoid memory leaks
		delete[] buffer;

		std::string empty = "";

		if (json["Current Answer"].GetString() != empty)
		{
			std::string answer = json["Current Answer"].GetString();
			if (answer == empty)
			{
				return;
			}
			Value& answers = json["Answer History"];
			const size_t num_answers = answers.MemberCount();
			int keynum = num_answers + 1;
			std::string ans_key = "answer" + std::to_string(keynum);

			Value answer_value;
			answer_value.SetString(answer.c_str(), answer.length(), json.GetAllocator());
			Value answer_key;
			answer_key.SetString(ans_key.c_str(), ans_key.length(), json.GetAllocator());
			answers.AddMember(answer_key, answer_value, json.GetAllocator());

			Value& new_answer = json["Current Answer"];
			new_answer.SetString("");
		}

		//writing the document back into a json file
		StringBuffer buffer_out;
		PrettyWriter<StringBuffer> writer(buffer_out);
		json.Accept(writer);
		
		ofstream update_file("calculator_data.json");
		update_file << buffer_out.GetString() << endl;

	}
	else 
	{
		if (character == "CLEAR")
		{
			ifstream file("calculator_data.json");
			ss << file.rdbuf();
			string json_str = ss.str();

			Document json;
			json.Parse(json_str.c_str());

			std::string empty = "";

			if (json["Current Answer"].GetString() != empty)
			{
				std::string answer = json["Current Answer"].GetString();
				if (answer == empty)
				{
					return;
				}
				Value& answers = json["Answer History"];
				const size_t num_answers = answers.MemberCount();
				int keynum = num_answers + 1;
				std::string ans_key = "answer" + std::to_string(keynum);

				Value answer_value;
				answer_value.SetString(answer.c_str(), answer.length(), json.GetAllocator());
				answers.AddMember(StringRef(ans_key.c_str()), answer_value, json.GetAllocator());

				Value& new_answer = json["Current Answer"];
				new_answer.SetString("");

				StringBuffer buf;
				PrettyWriter<StringBuffer> writer(buf);
				json.Accept(writer);

				ofstream update_file("calculator_data.json");
				update_file << buf.GetString() << endl;

				HWND hwnd = GetForegroundWindow();
				
				render_screen(hwnd);
				
			}
			if(json["Current Equation"].GetString() != empty)
			{
				Value& equation = json["Current Equation"];
				equation.SetString("");

				StringBuffer buf;
				PrettyWriter<StringBuffer> writer(buf);
				json.Accept(writer);

				ofstream update_file("calculator_data.json");
				update_file << buf.GetString() << endl;

				// Get a handle to the current window
				HWND hwnd = GetForegroundWindow();

				render_screen(hwnd);
			}
			
		}
		else if (character == "ENTER")
		{
			Math math;
			HWND hwnd = FindWindow(L"Calculator App", L"Calculator");
			double answer = math.Parser(hwnd);
			math.json_updator(answer);
		}
		else
		{
			//history button clicked
			History history;
			history.init_history(NULL, NULL, NULL, 1);

		}
	}
}

void Calculator_Screen::handle_mode(int message)
{
	if (message == 0)
	{
		stringstream ss;
		ifstream file("calculator_data.json");

		//parse the json into a string
		ss << file.rdbuf();
		string json_str = ss.str();

		//parse the string into a document object
		Document doc;
		doc.Parse(json_str.c_str());
		string light_mode = "Light Mode";
		
		Value& mode = doc["Mode"];

		mode.SetString(light_mode.c_str(), light_mode.length(), doc.GetAllocator());

		StringBuffer buffer_out;
		PrettyWriter<StringBuffer> writer(buffer_out);
		doc.Accept(writer);

		ofstream update_file("calculator_data.json");
		update_file << buffer_out.GetString() << endl;

		HWND hParent_wnd = FindWindow(L"Calculator App", L"Calculator");
		if (!hParent_wnd)
		{
			return;
		}

		BackgroundHandler bh;
		bh.handle_background(hParent_wnd);
	}
	if(message == 1)
	{
		stringstream ss;
		ifstream file("calculator_data.json");

		ss << file.rdbuf();
		string json_str = ss.str();

		Document doc;
		doc.Parse(json_str.c_str());

		string dark_mode = "Dark Mode";

		Value& mode = doc["Mode"];
		mode.SetString(dark_mode.c_str(), dark_mode.length(), doc.GetAllocator());

		StringBuffer buffer_out;
		PrettyWriter<StringBuffer> writer(buffer_out);
		doc.Accept(writer);

		ofstream update_file("calculator_data.json");
		update_file << buffer_out.GetString() << endl;

		HWND hParent_wnd = FindWindow(L"Calculator App", L"Calculator");
		if (!hParent_wnd)
		{
			return;
		}
		BackgroundHandler bh;
		
		bh.handle_background(hParent_wnd);
	}
}
