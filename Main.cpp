# include <Siv3D.hpp> // OpenSiv3D v0.4.2
# include "JSON.hpp"

JSON MakeDummy()
{
	JSON json;
	json[U"Dummy"][U"title"] = U"My title";
	json[U"Dummy"][U"width"] = 640;
	json[U"Dummy"][U"height"] = 480;
	return json;
}

void Test0()
{
	Console << U"[Test0]";

	JSON json;

	json[U"Types"][U"null"] = nullptr;

	json[U"Types"][U"bool.min"] = Smallest<bool>;
	json[U"Types"][U"bool.max"] = Largest<bool>;

	json[U"Types"][U"int8.min"] = Smallest<int8>;
	json[U"Types"][U"int8.max"] = Largest<int8>;
	json[U"Types"][U"int16.min"] = Smallest<int16>;
	json[U"Types"][U"int16.max"] = Largest<int16>;
	json[U"Types"][U"int32.min"] = Smallest<int32>;
	json[U"Types"][U"int32.max"] = Largest<int32>;
	json[U"Types"][U"int64.min"] = Smallest<int64>;
	json[U"Types"][U"int64.max"] = Largest<int64>;

	json[U"Types"][U"uint8.min"] = Smallest<uint8>;
	json[U"Types"][U"uint8.max"] = Largest<uint8>;
	json[U"Types"][U"uint16.min"] = Smallest<uint16>;
	json[U"Types"][U"uint16.max"] = Largest<uint16>;
	json[U"Types"][U"uint32.min"] = Smallest<uint32>;
	json[U"Types"][U"uint32.max"] = Largest<uint32>;
	json[U"Types"][U"uint64.min"] = Smallest<uint64>;
	json[U"Types"][U"uint64.max"] = Largest<uint64>;

	json[U"Types"][U"float"] = Math::PiF;
	json[U"Types"][U"double"] = Math::Pi;
	json[U"Types"][U"long double"] = Math::Pi_v<long double>;

	json[U"Types"][U"String.const char32*"] = U"Siv3D";
	json[U"Types"][U"String.String"] = String(U"Siv3D");
	json[U"Types"][U"String.StringView"] = StringView(U"Siv3D");

	json[U"Types"][U"Array.int32"] = { 10, 20, 30, 40 };
	json[U"Types"][U"Array.String"] = { U"Siv1D", U"Siv2D", U"Siv3D" };
	json[U"Types"][U"Array.Array.int32"] = Array<Array<int32>>{ { 1, 2, 3 }, {10, 20, 30}, {100, 200, 300} };

	json[U"Types"][U"Point"] = Point(11, 22);
	json[U"Types"][U"Color"] = Palette::Yellow;
	json[U"Types"][U"Circle"] = Circle(Scene::Center(), 100);

	json[U"Types"][U"Object"] = MakeDummy();

	Console << json << U'\n';
}

void Test1()
{
	Console << U"[Test1]";

	const JSON json =
	{
		{U"Window", {
			{U"title", U"My application"},
			{U"width", 800},
			{U"height", 600},
			{U"sizable", false}
		}},
		{U"Scene", {
			{U"background", ColorF(0.8, 0.9, 1.0)},
		}},
		{U"Array", {
			{U"values", {11, 22, 33, 44, 55}},
		}},
		{U"Items", {
			{{
				{U"label", U"Forest"},
				{U"pos", {
					{U"x", 100},
					{U"y", 100}
				}}
			},
			{
				{U"label", U"Ocean"},
				{U"pos", {
					{U"x", 300},
					{U"y", 200}
				}}
			},
			{
				{U"label", U"Mountain"},
				{U"pos", {
					{U"x", 500},
					{U"y", 100}
				}}
			}}
		}}
	};

	assert(json.hasElement(U"Window") == true);
	assert(json.hasElement(U"Scene") == true);
	assert(json.hasElement(U"Array") == true);
	assert(json.hasElement(U"Items") == true);
	assert(json.hasElement(U"aaa") == false);
	assert(json.hasElement(U"") == false);

	assert(json[U"Window"].hasElement(U"title") == true);
	assert(json[U"Window"].hasElement(U"width") == true);
	assert(json[U"Window"].hasElement(U"height") == true);
	assert(json[U"Window"].hasElement(U"sizable") == true);
	assert(json[U"Window"].hasElement(U"aaa") == false);
	assert(json[U"Window"].hasElement(U"") == false);

	assert(json[U"Window"][U"title"].getType() == JSONValueType::String);
	assert(json[U"Window"][U"width"].getType() == JSONValueType::Number);
	assert(json[U"Window"][U"height"].getType() == JSONValueType::Number);
	assert(json[U"Window"][U"sizable"].getType() == JSONValueType::Bool);

	assert(json[U"Window"][U"title"].isString() == true);
	assert(json[U"Window"][U"title"].isNumber() == false);
	assert(json[U"Window"][U"title"].isBool() == false);

	assert(json[U"Window"][U"width"].isString() == false);
	assert(json[U"Window"][U"width"].isNumber() == true);
	assert(json[U"Window"][U"width"].isBool() == false);

	assert(json[U"Window"][U"sizable"].isString() == false);
	assert(json[U"Window"][U"sizable"].isNumber() == false);
	assert(json[U"Window"][U"sizable"].isBool() == true);
}

void Test2()
{
	Console << U"[Test2]";

	JSON json =
	{
		{U"Window", {
			{U"title", U"My application"},
			{U"width", 800},
			{U"height", 600},
			{U"sizable", false}
		}},
		{U"Scene", {
			{U"background", ColorF(0.8, 0.9, 1.0)},
		}},
		{U"Array", {
			{U"values", {11, 22, 33, 44, 55}},
		}},
		{U"Items", {
			{{
				{U"label", U"Forest"},
				{U"pos", {
					{U"x", 100},
					{U"y", 100}
				}}
			},
			{
				{U"label", U"Ocean"},
				{U"pos", {
					{U"x", 300},
					{U"y", 200}
				}}
			},
			{
				{U"label", U"Mountain"},
				{U"pos", {
					{U"x", 500},
					{U"y", 100}
				}}
			}}
		}}
	};

	Console << json;
}

void Test3()
{
	Console << U"[Test3]";

	JSON json =
	{
		{U"Window", {
			{U"title", U"My application"},
			{U"width", 800},
			{U"height", 600},
			{U"sizable", false}
		}},
		{U"Scene", {
			{U"background", ColorF(0.8, 0.9, 1.0)},
		}},
		{U"Array", {
			{U"values", {11, 22, 33, 44, 55}},
		}},
		{U"Items", {
			{{
				{U"label", U"Forest"},
				{U"pos", {
					{U"x", 100},
					{U"y", 100}
				}}
			},
			{
				{U"label", U"Ocean"},
				{U"pos", {
					{U"x", 300},
					{U"y", 200}
				}}
			},
			{
				{U"label", U"Mountain"},
				{U"pos", {
					{U"x", 500},
					{U"y", 100}
				}}
			}}
		}}
	};

	json[U"Array"][U"values"][1] = 777;
	json.access(U"/Array/values/2") = 888;

	Console << json;
}

void Test4()
{
	Console << U"[Test4]";

	JSON json = JSON::Load(U"json/config.json");

	Console << json;

	Console << U"-------------------------";
	assert(json[U"Window"][U"title"].get<String>() == U"My application");
	assert(json[U"Window"][U"width"].get<int32>() == 800);
	assert(json[U"Window"][U"height"].get<int32>() == 600);
	assert(json[U"Window"][U"sizable"].get<bool>() == false);

	Console << U"-------------------------";
	assert(json[U"Window"][U"title"].getOpt<int32>() == none);
	assert(json[U"Window"][U"width"].getOpt<String>() == none);
	assert(json[U"Window"][U"height"].getOpt<bool>() == none);
	assert(json[U"Window"][U"sizable"].getOpt<String>() == none);

	Console << U"-------------------------";
	assert(json.access(U"/Window/title").get<String>() == U"My application");
	assert(json.access(U"/Window/width").get<int32>() == 800);
	assert(json.access(U"/Window/height").get<int32>() == 600);
	assert(json.access(U"/Window/sizable").get<bool>() == false);

	Console << U"-------------------------";
	assert(json[U"Window"].size() == 4);
	assert(json[U"Array"].size() == 1);
	assert(json[U"Array"][U"values"].size() == 5);

	Console << U"-------------------------";
	for (const auto& item : json)
	{
		Console << U"################";
		Console << item.key << U"=" << item.value;
	}
}

void Test5()
{
	Console << U"[Test5]";

	Console << U"\t[empty.json]";
	try
	{
		const JSON json = JSON::Load(U"json/empty.json");
		assert(json.isEmpty() == false);
		assert(!!json);
		Console << json.format(1, U'\t');
		Console << json.formatMinimum();
	}
	catch (const Error&)
	{
		assert(0);
	}

	Console << U"\t[nonexist.json]";
	try
	{
		const JSON json = JSON::Load(U"json/nonexist.json");
		assert(json.isEmpty() == true);
	}
	catch (const Error&)
	{
		assert(0);
	}

	Console << U"\t[invalid-blank.json]";
	try
	{
		const JSON json = JSON::Load(U"json/invalid-blank.json");
		assert(json.isEmpty() == true);
	}
	catch (const Error&)
	{
		assert(0);
	}

	Console << U"\t[invalid-syntax.json]";
	try
	{
		const JSON json = JSON::Load(U"json/invalid-syntax.json");
		assert(json.isEmpty() == true);
	}
	catch (const Error&)
	{
		assert(0);
	}
}

void Test6()
{
	Console << U"[Test6]";

	Console << U"\t[empty.json -AllowExceptions]";
	try
	{
		const JSON json = JSON::Load(U"json/empty.json", JSON::AllowExceptions);
		assert(json.isEmpty() == false);
	}
	catch (const Error&)
	{
		assert(0);
	}

	Console << U"\t[nonexist.json -AllowExceptions]";
	try
	{
		const JSON json = JSON::Load(U"json/nonexist.json", JSON::AllowExceptions);
		assert(0);
	}
	catch (const Error& e)
	{
		Console << e.what();
	}

	Console << U"\t[invalid-blank.json -AllowExceptions]";
	try
	{
		const JSON json = JSON::Load(U"json/invalid-blank.json", JSON::AllowExceptions);
		assert(0);
	}
	catch (const Error& e)
	{
		Console << e.what();
	}

	Console << U"\t[invalid-syntax.json -AllowExceptions]";
	try
	{
		const JSON json = JSON::Load(U"json/invalid-syntax.json", JSON::AllowExceptions);
		assert(0);
	}
	catch (const Error& e)
	{
		Console << e.what();
	}
}


void Test7()
{
	Console << U"[Test7]";

	{
		JSON json;
		Console << json;
		for ([[maybe_unused]] const auto& element : json)
		{
			assert(0);
		}
	}

	{
		JSON json = JSON::Invalid();
		Console << json;
		for ([[maybe_unused]] const auto& element : json)
		{
			assert(0);
		}
	}
}

void Test8()
{
	Console << U"[Test8]";

	const JSON json = JSON::Load(U"json/test.json", JSON::AllowExceptions);
	try
	{
		Console << json[U"value.string"].get<bool>();
		assert(0);
	}
	catch (const Error & e)
	{
		Console << e.what();
	}

	try
	{
		Console << json[U"value.bool"].get<String>();
		assert(0);
	}
	catch (const Error & e)
	{
		Console << e.what();
	}

	try
	{
		Console << json[U"nonexist"].get<String>();
		assert(0);
	}
	catch (const Error & e)
	{
		Console << e.what();
	}

	try
	{
		Console << json[0];
		assert(0);
	}
	catch (const Error & e)
	{
		Console << e.what();
	}

	try
	{
		Console << json[U"values"][3];
		assert(0);
	}
	catch (const Error & e)
	{
		Console << e.what();
	}
}

void Main()
{
	Test0();
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();

	while (System::Update())
	{

	}
}
