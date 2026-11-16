#ifndef DOUBLE_STACK_HPP
#define DOUBLE_STACK_HPP

#include <initializer_list>
#include <stack>
#include <type_traits>
#include <utility>
#include <vector>

/**
 * @brief Contiene dos pilas del mismo tipo en un único vector.
 *
 * La primera pila ocupa el inicio del vector y la segunda, el final. El hueco
 * entre ambas se usa al insertar elementos.
 *
 * @tparam T Tipo de los elementos. Debe ser construible por defecto, movible
 * y asignable por copia y por movimiento.
 */
template <typename T>
  requires std::is_default_constructible_v<T> &&
           std::is_move_constructible_v<T> && std::is_copy_assignable_v<T> &&
           std::is_move_assignable_v<T>
class double_stack {

public:
  // ---------------------------------------------------------------------------
  // Tipos y constantes
  // ---------------------------------------------------------------------------

  /** @brief Tipo de los elementos almacenados. */
  using value_type = T;

  /** @brief Referencia modificable a un elemento. */
  using reference = T&;

  /** @brief Referencia de solo lectura a un elemento. */
  using const_reference = const T&;

  /** @brief Tipo usado para representar tamaños e índices. */
  using size_type = typename std::vector<T>::size_type;

  /** @brief Contenedor usado para recibir secuencias de elementos. */
  using container_type = std::vector<T>;

  /** @brief Identificador de la primera pila. */
  static constexpr int NUM_PILA_FIRST = 1;

  /** @brief Identificador de la segunda pila. */
  static constexpr int NUM_PILA_SECOND = 0;

private:
  // ---------------------------------------------------------------------------
  // Miembros de datos
  // ---------------------------------------------------------------------------

  /** @brief Vector que almacena los elementos y el espacio entre las pilas. */
  container_type data_;

  /** @brief Número de elementos de la primera pila. */
  size_type size_first_ = 0;

  /** @brief Número de elementos de la segunda pila. */
  size_type size_second_ = 0;

public:
  // ---------------------------------------------------------------------------
  // Constructores
  // ---------------------------------------------------------------------------

  /**
   * @brief Construye dos pilas vacías.
   *
   * @post Ambas pilas están vacías.
   */
  constexpr double_stack() noexcept = default;

  /**
   * @brief Construye ambas pilas a partir de listas de inicialización.
   *
   * En la primera pila, el último elemento de la lista queda en la cima. En la
   * segunda, el primero queda en la cima.
   *
   * @param first Elementos de la primera pila.
   * @param second Elementos de la segunda pila.
   */
  constexpr double_stack(std::initializer_list<T> first,
                         std::initializer_list<T> second);

  /**
   * @brief Construye la primera pila desde una lista y la segunda desde otra
   * fuente admitida.
   *
   * @tparam Second Tipo de la fuente de la segunda pila.
   * @param first Elementos de la primera pila.
   * @param second Fuente de elementos para la segunda pila.
   */
  template <typename Second>
  constexpr double_stack(std::initializer_list<T> first, Second&& second);

  /**
   * @brief Construye la primera pila desde una fuente y la segunda desde una
   * lista.
   *
   * @tparam First Tipo de la fuente de la primera pila.
   * @param first Fuente de elementos para la primera pila.
   * @param second Elementos de la segunda pila.
   */
  template <typename First>
  constexpr double_stack(First&& first, std::initializer_list<T> second);

  /**
   * @brief Construye ambas pilas desde fuentes admitidas.
   *
   * @tparam First Tipo de la fuente de la primera pila.
   * @tparam Second Tipo de la fuente de la segunda pila.
   * @param first Fuente de elementos para la primera pila.
   * @param second Fuente de elementos para la segunda pila.
   */
  template <typename First, typename Second>
  constexpr double_stack(First&& first, Second&& second);

  /**
   * @brief Construye la primera pila desde un rango y la segunda desde una
   * fuente.
   *
   * @tparam It Tipo de los iteradores del primer rango.
   * @tparam Second Tipo de la fuente de la segunda pila.
   * @param first_begin Inicio del rango de la primera pila.
   * @param first_end Fin del rango de la primera pila.
   * @param second Fuente de elementos para la segunda pila.
   * @pre Los iteradores delimitan un rango válido.
   */
  template <typename It, typename Second>
  constexpr double_stack(It first_begin, It first_end, Second&& second);

  /**
   * @brief Construye la primera pila desde un rango y la segunda desde una
   * lista.
   *
   * @tparam It Tipo de los iteradores del primer rango.
   * @param first_begin Inicio del rango de la primera pila.
   * @param first_end Fin del rango de la primera pila.
   * @param second Elementos de la segunda pila.
   * @pre Los iteradores delimitan un rango válido.
   */
  template <typename It>
  constexpr double_stack(It first_begin, It first_end,
                         std::initializer_list<T> second);

  /**
   * @brief Construye la primera pila desde una fuente y la segunda desde un
   * rango.
   *
   * @tparam First Tipo de la fuente de la primera pila.
   * @tparam It Tipo de los iteradores del segundo rango.
   * @param first Fuente de elementos para la primera pila.
   * @param second_begin Inicio del rango de la segunda pila.
   * @param second_end Fin del rango de la segunda pila.
   * @pre Los iteradores delimitan un rango válido.
   */
  template <typename First, typename It>
  constexpr double_stack(First&& first, It second_begin, It second_end);

  /**
   * @brief Construye la primera pila desde una lista y la segunda desde un
   * rango.
   *
   * @tparam It Tipo de los iteradores del segundo rango.
   * @param first Elementos de la primera pila.
   * @param second_begin Inicio del rango de la segunda pila.
   * @param second_end Fin del rango de la segunda pila.
   * @pre Los iteradores delimitan un rango válido.
   */
  template <typename It>
  constexpr double_stack(std::initializer_list<T> first, It second_begin,
                         It second_end);

  /**
   * @brief Construye ambas pilas desde dos rangos.
   *
   * @tparam It1 Tipo de los iteradores del primer rango.
   * @tparam It2 Tipo de los iteradores del segundo rango.
   * @param first_begin Inicio del rango de la primera pila.
   * @param first_end Fin del rango de la primera pila.
   * @param second_begin Inicio del rango de la segunda pila.
   * @param second_end Fin del rango de la segunda pila.
   * @pre Cada par de iteradores delimita un rango válido.
   */
  template <typename It1, typename It2>
  constexpr double_stack(It1 first_begin, It1 first_end, It2 second_begin,
                         It2 second_end);

  /**
   * @brief Copia las dos pilas.
   *
   * @param other Objeto que se copia.
   */
  constexpr double_stack(const double_stack& other);

  /**
   * @brief Construye el objeto trasladando las pilas de otro.
   *
   * @param other Objeto del que se toman los elementos.
   * @post El objeto de origen queda vacío.
   */
  constexpr double_stack(double_stack&& other);

  // ---------------------------------------------------------------------------
  // Asignación y destrucción
  // ---------------------------------------------------------------------------

  /** @brief Destruye el objeto y sus elementos. */
  constexpr ~double_stack() = default;

  /**
   * @brief Copia las pilas de otro objeto.
   *
   * @param other Objeto que se copia.
   * @return Referencia a este objeto.
   */
  constexpr double_stack& operator=(const double_stack& other);

  /**
   * @brief Sustituye las pilas trasladando las de otro objeto.
   *
   * @param other Objeto del que se toman los elementos.
   * @return Referencia a este objeto.
   * @post El objeto de origen queda vacío.
   */
  constexpr double_stack& operator=(double_stack&& other);

  // ---------------------------------------------------------------------------
  // Acceso a los elementos
  // ---------------------------------------------------------------------------

  /**
   * @brief Devuelve la cima de una de las pilas.
   *
   * @param self Objeto cuya cima se consulta.
   * @param num_pila Identificador de la pila.
   * @return Referencia a la cima, con la categoría de referencia de este
   * objeto.
   * @pre num_pila es NUM_PILA_FIRST o NUM_PILA_SECOND y esa pila no está vacía.
   */
  [[nodiscard]] constexpr auto&& top(this auto&& self, int num_pila) noexcept;

  /**
   * @brief Indica si una de las pilas está vacía.
   *
   * @param num_pila Identificador de la pila.
   * @return true si la pila está vacía.
   * @pre num_pila es NUM_PILA_FIRST o NUM_PILA_SECOND.
   */
  [[nodiscard]] constexpr bool empty(int num_pila) const noexcept;

  /**
   * @brief Devuelve el número de elementos de una pila.
   *
   * @param num_pila Identificador de la pila.
   * @return Número de elementos.
   * @pre num_pila es NUM_PILA_FIRST o NUM_PILA_SECOND.
   */
  [[nodiscard]] constexpr size_type size(int num_pila) const noexcept;

  /**
   * @brief Devuelve una copia de una de las pilas como std::stack.
   *
   * @param num_pila Identificador de la pila.
   * @return Copia de la pila indicada, con la misma cima.
   * @pre num_pila es NUM_PILA_FIRST o NUM_PILA_SECOND.
   * @post Este objeto no cambia.
   */
  [[nodiscard]] std::stack<T> copy_stack(int num_pila) const;

  // ---------------------------------------------------------------------------
  // Modificadores
  // ---------------------------------------------------------------------------

  /**
   * @brief Inserta una copia del valor en una pila.
   *
   * @param value Valor que se copia.
   * @param num_pila Identificador de la pila.
   * @pre num_pila es NUM_PILA_FIRST o NUM_PILA_SECOND.
   * @post El tamaño de la pila indicada aumenta en uno.
   */
  constexpr void push(const value_type& value, int num_pila);

  /**
   * @brief Inserta un valor trasladándolo a una pila.
   *
   * @param value Valor que se traslada.
   * @param num_pila Identificador de la pila.
   * @pre num_pila es NUM_PILA_FIRST o NUM_PILA_SECOND.
   * @post El tamaño de la pila indicada aumenta en uno.
   */
  constexpr void push(value_type&& value, int num_pila);

  /**
   * @brief Construye e inserta un elemento en una pila.
   *
   * @tparam Args Tipos de los argumentos del constructor de T.
   * @param num_pila Identificador de la pila.
   * @param args Argumentos para construir el elemento.
   * @return Referencia al elemento insertado.
   * @pre num_pila es NUM_PILA_FIRST o NUM_PILA_SECOND.
   * @post El tamaño de la pila indicada aumenta en uno.
   */
  template <class... Args>
  constexpr reference emplace(int num_pila, Args&&... args);

  /**
   * @brief Elimina la cima de una pila.
   *
   * @param num_pila Identificador de la pila.
   * @pre num_pila es NUM_PILA_FIRST o NUM_PILA_SECOND y esa pila no está vacía.
   * @post El tamaño de la pila indicada disminuye en uno.
   */
  constexpr void pop(int num_pila);

  /**
   * @brief Intercambia el contenido de este objeto con otro.
   * @param other Objeto con el que se intercambia el contenido.
   */
  constexpr void swap(double_stack& other);

  // ---------------------------------------------------------------------------
  // Comparación
  // ---------------------------------------------------------------------------

  /**
   * @brief Compara el contenido de ambas pilas.
   *
   * @param other Objeto con el que se compara.
   * @return true si las dos pilas tienen los mismos elementos en el mismo
   * orden.
   */
  [[nodiscard]] constexpr bool operator==(const double_stack& other) const;

  /**
   * @brief Indica si el contenido de alguna de las pilas es distinto.
   *
   * @param other Objeto con el que se compara.
   * @return true si las dos pilas no tienen el mismo contenido.
   */
  [[nodiscard]] constexpr bool operator!=(const double_stack& other) const;

private:
  // ---------------------------------------------------------------------------
  // Funciones auxiliares
  // ---------------------------------------------------------------------------

  /**
   * @brief Inicializa la primera pila desde un objeto std::stack.
   * @param first Pila de la que se copian los elementos.
   */
  constexpr void ConstructFirst(std::stack<T> first);

  /**
   * @brief Inicializa la primera pila desde una lista.
   * @param first Elementos que se copian.
   */
  constexpr void ConstructFirst(std::initializer_list<T> first);

  /**
   * @brief Inicializa la primera pila desde un vector.
   * @param first Vector cuyos elementos se trasladan.
   */
  constexpr void ConstructFirst(container_type first);

  /**
   * @brief Inicializa la primera pila desde un rango de iteradores.
   * @tparam It Tipo de los iteradores.
   * @param first_1 Inicio del rango.
   * @param last_1 Fin del rango.
   */
  template <typename It> constexpr void ConstructFirst(It first_1, It last_1);

  /**
   * @brief Inicializa la segunda pila desde un objeto std::stack.
   * @param second Pila de la que se copian los elementos.
   */
  constexpr void ConstructSecond(std::stack<T> second);

  /**
   * @brief Inicializa la segunda pila desde una lista.
   * @param second Elementos que se copian.
   */
  constexpr void ConstructSecond(std::initializer_list<T> second);

  /**
   * @brief Inicializa la segunda pila desde un vector.
   * @param second Vector cuyos elementos se trasladan.
   */
  constexpr void ConstructSecond(container_type second);

  /**
   * @brief Inicializa la segunda pila desde un rango de iteradores.
   * @tparam It Tipo de los iteradores.
   * @param first_2 Inicio del rango.
   * @param last_2 Fin del rango.
   */
  template <typename It> constexpr void ConstructSecond(It first_2, It last_2);

  /**
   * @brief Reserva el espacio inicial para la primera pila.
   * @param first Número de elementos que tendrá la primera pila.
   */
  constexpr void PrepareFirst(size_type first);

  /**
   * @brief Reserva espacio para ambas pilas, redondeando a potencia de dos.
   * @param second Número de elementos que tendrá la segunda pila.
   */
  constexpr void PrepareSecond(size_type second);

  /**
   * @brief Devuelve la potencia de dos igual o superior al valor indicado.
   * @param num Valor que se redondea.
   * @return Potencia de dos calculada.
   */
  constexpr size_type UpperTwoPower(size_type num) const noexcept;
};

/**
 * @brief Intercambia dos objetos double_stack.
 *
 * @tparam T Tipo de los elementos de ambas pilas.
 * @param first Primer objeto.
 * @param second Segundo objeto.
 */
template <typename T>
constexpr void swap(double_stack<T>& first, double_stack<T>& second);

#include "double_stack.tpp"

#endif // DOUBLE_STACK_HPP
