# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	namespace detail
	{
		struct JSONIteratorDetail;
		struct JSONConstIteratorDetail;
		class JSONDetail;
	}

	class JSONIterator;
	class JSONConstIterator;
	class JSON;
	struct JSONItem;

	class JSONIterator
	{
	private:

		std::shared_ptr<detail::JSONIteratorDetail> m_detail;

	public:

		JSONIterator() = default;

		JSONIterator(const JSONIterator&);

		explicit JSONIterator(const detail::JSONIteratorDetail&);

		JSONIterator& operator =(const JSONIterator& rhs);

		JSONIterator& operator++();

		JSONIterator operator++(int);

		[[nodiscard]] JSONIterator operator +(size_t index) const;

		[[nodiscard]] JSONItem operator *() const;

		[[nodiscard]] String key() const;

		[[nodiscard]] JSON value() const;

		[[nodiscard]] bool operator ==(const JSONIterator& other) const noexcept;

		[[nodiscard]] bool operator !=(const JSONIterator& other) const noexcept;
	};

	class JSONConstIterator
	{
	private:

		std::shared_ptr<detail::JSONConstIteratorDetail> m_detail;

	public:

		JSONConstIterator() = default;

		JSONConstIterator(const JSONConstIterator&);

		explicit JSONConstIterator(const detail::JSONConstIteratorDetail&);

		JSONConstIterator& operator =(const JSONConstIterator& rhs);

		JSONConstIterator& operator++();

		JSONConstIterator operator++(int);

		[[nodiscard]] JSONConstIterator operator +(size_t index) const;

		[[nodiscard]] const JSONItem operator *() const;

		[[nodiscard]] String key() const;

		[[nodiscard]] const JSON value() const;

		[[nodiscard]] bool operator ==(const JSONConstIterator& other) const noexcept;

		[[nodiscard]] bool operator !=(const JSONConstIterator& other) const noexcept;
	};

	class JSON
	{
	private:

		std::shared_ptr<detail::JSONDetail> m_detail;

		bool m_isValid = true;

		struct Invalid_ {};

		JSON(Invalid_);

		template <class Type, std::enable_if_t<std::is_integral_v<Type> && !std::is_same_v<bool, std::decay_t<Type>>>* = nullptr>
		Optional<Type> getOpt_() const
		{
			if (const auto opt = getOptInt64())
			{
				return static_cast<Type>(opt.value());
			}

			return none;
		}

		template <class Type, std::enable_if_t<std::is_floating_point_v<Type>> * = nullptr>
		Optional<Type> getOpt_() const
		{
			if (const auto opt = getOptDouble())
			{
				return ParseOpt<Type>(opt.value());
			}

			return none;
		}

		template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>> * = nullptr>
		Optional<Type> getOpt_() const
		{
			if (const auto opt = getOptString())
			{
				return static_cast<Type>(opt.value());
			}

			return none;
		}

		Optional<String> getOptString() const;

		Optional<int64> getOptInt64() const;

		Optional<double> getOptDouble() const;

		Optional<bool> getOptBool() const;

	public:

		using iterator = JSONIterator;

		using const_iterator = JSONConstIterator;

		static constexpr bool AllowExceptions = true;

		JSON();

		JSON(std::shared_ptr<detail::JSONDetail>&& detail);

		JSON(std::nullptr_t);

		JSON(const JSON&) = default;

		JSON(JSON&&) = default;

		JSON(const std::initializer_list<std::pair<String, JSON>>& list);

		JSON(const Array<JSON>& array);

		template <class Type, std::enable_if_t<!std::is_same_v<std::decay_t<Type>, JSON> && std::is_constructible_v<JSON, Type>>* = nullptr>
		JSON(const Array<Type>& arr)
			: JSON(arr.map([](auto&& v){ return JSON(v); })) {}

		template <class Type, std::enable_if_t<std::is_constructible_v<JSON, Type>>* = nullptr>
		JSON(const std::initializer_list<Type>& list)
			: JSON(Array(list)) {}

		JSON(StringView value);

		template <class StringViewish, std::enable_if_t<std::is_constructible_v<StringView, StringViewish>>* = nullptr>
		JSON(const StringViewish& value)
			: JSON(StringView(value)) {}

		JSON(int64 value);

		JSON(uint64 value);

		JSON(double value);

		JSON(bool value);

		template <class Integer, std::enable_if_t<std::is_integral_v<Integer> && std::is_signed_v<Integer>>* = nullptr>
		JSON(Integer value)
			: JSON(static_cast<int64>(value)) {}

		template <class Integer, std::enable_if_t<std::is_unsigned_v<Integer>>* = nullptr>
		JSON(Integer value)
			: JSON(static_cast<uint64>(value)) {}

		template <class Float, std::enable_if_t<std::is_floating_point_v<Float>>* = nullptr>
		JSON(Float value)
			: JSON(static_cast<double>(value)) {}

		template <class Type,
			std::enable_if_t<!std::is_constructible_v<StringView, Type> && !std::is_arithmetic_v<Type>> * = nullptr>
		JSON(const Type& value)
			: JSON(Format(value)) {}

		// JSONValueType::Null
		JSON& operator =(std::nullptr_t);
		
		// JSONValueType::Object
		JSON& operator =(const JSON& value);

		// JSONValueType::Object
		JSON& operator =(const std::initializer_list<std::pair<String, JSON>>& list);

		// JSONValueType::Array
		JSON& operator =(const Array<JSON>& array);

		// JSONValueType::Array
		template <class Type, std::enable_if_t<!std::is_same_v<std::decay_t<Type>, JSON> && std::is_constructible_v<JSON, Type>> * = nullptr>
		JSON& operator =(const Array<Type>& arr)
		{
			return (*this = arr.map([](auto&& v){ return JSON(v); }));
		}

		// JSONValueType::Array
		template <class Type, std::enable_if_t<std::is_constructible_v<JSON, Type>>* = nullptr>
		JSON& operator =(const std::initializer_list<Type>& list)
		{
			return (*this = Array(list));
		}

		// JSONValueType::String
		JSON& operator =(StringView value);

		// JSONValueType::String
		template <class StringViewish, std::enable_if_t<std::is_constructible_v<StringView, StringViewish>>* = nullptr>
		JSON& operator =(const StringViewish& value)
		{
			return operator =(StringView(value));
		}

		// JSONValueType::Number
		JSON& operator =(int64 value);

		// JSONValueType::Number
		JSON& operator =(uint64 value);

		// JSONValueType::Number
		JSON& operator =(double value);

		// JSONValueType::Bool
		JSON& operator =(bool value);

		template <class Integer, std::enable_if_t<std::is_integral_v<Integer> && std::is_signed_v<Integer>>* = nullptr>
		JSON& operator =(Integer value)
		{
			return operator =(static_cast<int64>(value));
		}

		template <class Integer, std::enable_if_t<std::is_unsigned_v<Integer>>* = nullptr>
		JSON& operator =(Integer value)
		{
			return operator =(static_cast<uint64>(value));
		}

		template <class Float, std::enable_if_t<std::is_floating_point_v<Float>>* = nullptr>
		JSON& operator =(Float value)
		{
			return operator =(static_cast<double>(value));
		}

		template <class Type,
			std::enable_if_t<!std::is_constructible_v<StringView, Type> && !std::is_arithmetic_v<Type>>* = nullptr,
			class = decltype(Formatter(std::declval<FormatData&>(), std::declval<Type>()))>
		JSON& operator =(const Type& value)
		{
			return operator =(Format(value));
		}

		[[nodiscard]] bool operator ==(const JSON& other) const;

		[[nodiscard]] bool operator !=(const JSON& other) const;

		// Load や Parse に失敗したときのみ true
		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const;

		[[nodiscard]] bool isNull() const;

		[[nodiscard]] bool isBool() const;

		[[nodiscard]] bool isNumber() const;

		[[nodiscard]] bool isInteger() const;

		[[nodiscard]] bool isUnsigned() const;

		[[nodiscard]] bool isFloat() const;

		[[nodiscard]] bool isString() const;

		[[nodiscard]] bool isArray() const;

		[[nodiscard]] bool isObject() const;

		[[nodiscard]] JSONValueType getType() const;

		[[nodiscard]] bool hasElement(StringView name) const;

		[[nodiscard]] String getString() const;

		template <class Type>
		[[nodiscard]] Type get() const
		{
			if (const auto opt = getOpt<Type>())
			{
				return opt.value();
			}
			else
			{
				throw Error(U"JSON::get(): Invalid JSON type (value: {})"_fmt(*this));
			}
		}

		template <class Type, class U>
		[[nodiscard]] Type getOr(U&& defaultValue) const
		{
			return getOpt<Type>().value_or(std::forward<U>(defaultValue));
		}

		template <class Type>
		[[nodiscard]] Optional<Type> getOpt() const
		{
			return getOpt_<Type>();
		}

		template <>
		[[nodiscard]] Optional<String> getOpt<String>() const
		{
			return getOptString();
		}

		template <>
		[[nodiscard]] Optional<int64> getOpt<int64>() const
		{
			return getOptInt64();
		}

		template <>
		[[nodiscard]] Optional<double> getOpt<double>() const
		{
			return getOptDouble();
		}

		template <>
		[[nodiscard]] Optional<bool> getOpt<bool>() const
		{
			return getOptBool();
		}

		JSON operator [](StringView name);

		const JSON operator [](StringView name) const;

		JSON operator [](size_t index);

		const JSON operator [](size_t index) const;

		JSON access(StringView jsonPointer);

		const JSON access(StringView jsonPointer) const;

		void clear() const;

		void erase(StringView name);

		// [Siv3D ToDo]
		// void erase(???); 他のオーバーロード

		// [Siv3D ToDo]
		//[[nodiscard]] iterator find(const StringView name)

		// [Siv3D ToDo]
		//[[nodiscard]] const_iterator find(const StringView name)

		[[nodiscard]] iterator begin();

		[[nodiscard]] const_iterator begin() const;

		[[nodiscard]] iterator end();

		[[nodiscard]] const_iterator end() const;

		[[nodiscard]] size_t size() const;

		[[nodiscard]] String format(char32 space = U' ', size_t spaceCount = 2) const;

		[[nodiscard]] String formatMinimum() const;

		bool save(FilePathView path) const;

		bool saveMinimum(FilePathView path) const;

		[[nodiscard]] static JSON Invalid();

		[[nodiscard]] static JSON Load(FilePathView path, bool allowExceptions = false);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>> * = nullptr>
		[[nodiscard]] static JSON Load(Reader&& reader, bool allowExceptions = false)
		{
			return Load(std::make_shared<Reader>(std::move(reader)));
		}

		[[nodiscard]] static JSON Load(const std::shared_ptr<IReader>& reader, bool allowExceptions = false);

		[[nodiscard]] static JSON Parse(StringView str, bool allowExceptions = false);
	};

	struct JSONItem
	{
		String key;

		JSON value;
	};

	void Formatter(FormatData& formatData, const JSON& json);
}
