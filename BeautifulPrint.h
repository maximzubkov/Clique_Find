// Функции для красивого вывода промежуточных результатов выполнения программы

/// Обычно для подобного функционала используются namespaces, это полезно, потому что в больших проектах могут быть
/// десятки функций типа print(...)
#pragma once

namespace Logger{
	inline void vertexes (std::ostream& ostr, uint64_t num, int max){
		int i = 0;
		ostr << "(";
		while (num > 0){
			if ((num & 1ULL) == 1ULL){
				ostr << max - i - 1<< " ";
			}
			i++;
			num = num >> 1;
		}
		ostr << ")";
		ostr << "\n";
	};

	inline void binary (std::ostream& ostr, uint64_t num){
		int i = 0;
		std::vector<int> v; /// не стоит использовать однобуквенные переменные нигде, кроме счетчиков в циклах
		while (num > 0){
			v.push_back(num % 2);
			i++;
			num = num >> 1;
		}

		/// С языке си начиная с 11 стандарта, а так же в с++ обычно объявление счетчика обычно
		/// происходит в теле цикла, то есть
		/// for (int i = static_cast<int>(v.size()) - 1; i >= 0; --i) {
		///	...
		/// }

		for (i = static_cast<int>(v.size()) - 1; i >= 0; --i) {
			ostr << v[i];
		}

		/// Есть концепция обратных итераторов, кстати
		/// for (auto iter = v.rbegin(); iter != v.rend(); ++iter) {
		///		std::cout << *iter;
		/// }
		/// rbegin/rend - справа налево, begin/end - слева направо

		ostr << " " << v.size() << "\n";
	};



	/// Ну все аналогично
	inline void print(std::ostream& ostr, char set, int in_clique, uint64_t cli, uint64_t all, int max){
		ostr << set<< ": " << cli << " in clique: " <<  in_clique << "; ";
		vertexes(ostr, cli, max);
		ostr << "all: ";
		vertexes(ostr, all, max);
	};
} // namespace Logger