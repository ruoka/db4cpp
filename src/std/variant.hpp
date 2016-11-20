#pragma once

/*

// Header <variant> synopsis

namespace std {
    // 20.7.2, variant of value types
    template <class... Types> class variant;
    // 20.7.3, variant helper classes
    template <class T> struct variant_size; // undefined
    template <class T> struct variant_size<const T>;
    template <class T> struct variant_size<volatile T>;
    template <class T> struct variant_size<const volatile T>;
    template <class T> constexpr size_t variant_size_v = variant_size<T>::value;
    template <class... Types> struct variant_size<variant<Types...>>;
    template <size_t I, class T> struct variant_alternative; // undefined
    template <size_t I, class T> struct variant_alternative<I, const T>;
    template <size_t I, class T> struct variant_alternative<I, volatile T>;
    template <size_t I, class T> struct variant_alternative<I, const volatile T>;
    template <size_t I, class T> using variant_alternative_t = typename variant_alternative<I, T>::type;
    template <size_t I, class... Types> struct variant_alternative<I, variant<Types...>>;
    constexpr size_t variant_npos = -1;
    // 20.7.4, value access
    template <class T, class... Types> constexpr bool holds_alternative(const variant<Types...>&) noexcept;
    template <size_t I, class... Types> constexpr variant_alternative_t<I, variant<Types...>>& get(variant<Types...>&);
    template <size_t I, class... Types> constexpr variant_alternative_t<I, variant<Types...>>&& get(variant<Types...>&&);
    template <size_t I, class... Types> constexpr variant_alternative_t<I, variant<Types...>> const& get(const variant<Types...>&);
    template <size_t I, class... Types> constexpr variant_alternative_t<I, variant<Types...>> const&& get(const variant<Types...>&&);
    template <class T, class... Types> constexpr T& get(variant<Types...>&);
    template <class T, class... Types> constexpr T&& get(variant<Types...>&&);
    template <class T, class... Types> constexpr const T& get(const variant<Types...>&);
    template <class T, class... Types> constexpr const T&& get(const variant<Types...>&&);
    template <size_t I, class... Types> constexpr add_pointer_t<variant_alternative_t<I, variant<Types...>>> get_if(variant<Types...>*) noexcept;
    template <size_t I, class... Types> constexpr add_pointer_t<const variant_alternative_t<I, variant<Types...>>> get_if(const variant<Types...>*) noexcept;
    template <class T, class... Types> constexpr add_pointer_t<T> get_if(variant<Types...>*) noexcept;
    template <class T, class... Types> constexpr add_pointer_t<const T> get_if(const variant<Types...>*) noexcept;
    // 20.7.5, relational operators
    template <class... Types> constexpr bool operator==(const variant<Types...>&, const variant<Types...>&);
    template <class... Types> constexpr bool operator!=(const variant<Types...>&, const variant<Types...>&);
    template <class... Types> constexpr bool operator<(const variant<Types...>&, const variant<Types...>&);
    template <class... Types> constexpr bool operator>(const variant<Types...>&, const variant<Types...>&);
    template <class... Types> constexpr bool operator<=(const variant<Types...>&, const variant<Types...>&);
    template <class... Types> constexpr bool operator>=(const variant<Types...>&, const variant<Types...>&);
    // 20.7.6, visitation
    template <class Visitor, class... Variants> constexpr see below visit(Visitor&&, Variants&&...);
    // 20.7.7,
    class monostate struct monostate;
    // 20.7.8, monostate relational operators
    constexpr bool operator<(monostate, monostate) noexcept;
    constexpr bool operator>(monostate, monostate) noexcept;
    constexpr bool operator<=(monostate, monostate) noexcept;
    constexpr bool operator>=(monostate, monostate) noexcept;
    constexpr bool operator==(monostate, monostate) noexcept;
    constexpr bool operator!=(monostate, monostate) noexcept;
    // 20.7.9, specialized algorithms
    template <class... Types> void swap(variant<Types...>&, variant<Types...>&) noexcept(see below);
    // 20.7.10,
    class bad_variant_access class bad_variant_access;
    // 20.7.11, hash support
    template <class T> struct hash;
    template <class... Types> struct hash<variant<Types...>>;
    template <> struct hash<monostate>;
    // 20.7.12, allocator-related traits
    template <class T, class Alloc> struct uses_allocator;
    template <class... Types, class Alloc> struct uses_allocator<variant<Types...>, Alloc>;
} // namespace std

namespace std {
    template <class... Types>
    class variant {
    public:
        // 20.7.2.1, constructors
        constexpr variant() noexcept(see below);
        variant(const variant&);
        variant(variant&&) noexcept(see below);
        template <class T> constexpr variant(T&&) noexcept(see below);
        template <class T, class... Args> constexpr explicit variant(in_place_type<T>, Args&&...);
        template <class T, class U, class... Args> constexpr explicit variant(in_place_type<T>, initializer_list<U>, Args&&...);
        template <size_t I, class... Args> constexpr explicit variant(in_place_index_t<I>, Args&&...);
        template <size_t I, class U, class... Args> constexpr explicit variant(in_place_index_t<I>, initializer_list<U>, Args&&...);
        // allocator-extended constructors
        template <class Alloc> variant(allocator_arg_t, const Alloc&);
        template <class Alloc> variant(allocator_arg_t, const Alloc&, const variant&);
        template <class Alloc> variant(allocator_arg_t, const Alloc&, variant&&);
        template <class Alloc, class T> variant(allocator_arg_t, const Alloc&, T&&);
        template <class Alloc, class T, class... Args> variant(allocator_arg_t, const Alloc&, in_place_type<T>, Args&&...);
        template <class Alloc, class T, class U, class... Args> variant(allocator_arg_t, const Alloc&, in_place_type<T>, initializer_list<U>, Args&&...);
        template <class Alloc, size_t I, class... Args> variant(allocator_arg_t, const Alloc&, in_place_index_t<I>, Args&&...);
        template <class Alloc, size_t I, class U, class... Args> variant(allocator_arg_t, const Alloc&, in_place_index_t<I>, initializer_list<U>, Args&&...);
        // 20.7.2.2, destructor
        ~variant();
        // 20.7.2.3, assignment
        variant& operator=(const variant&);
        variant& operator=(variant&&) noexcept(see below);
        template <class T> variant& operator=(T&&) noexcept(see below);
        // 20.7.2.4, modifiers
        template <class T, class... Args> void emplace(Args&&...);
        template <class T, class U, class... Args> void emplace(initializer_list<U>, Args&&...);
        template <size_t I, class... Args> void emplace(Args&&...);
        template <size_t I, class U, class... Args> void emplace(initializer_list<U>, Args&&...);
        // 20.7.2.5, value status
        constexpr bool valueless_by_exception() const noexcept;
        constexpr size_t index() const noexcept;
        // 20.7.2.6, swap
        void swap(variant&) noexcept(see below); };
} // namespace std

*/

#include <tuple>
#include <array>
#include <utility>
#include <functional>
#include <cassert>

namespace std {

template <class Type, class... Types>
union __variant_storage; // undefined

struct __trivial{};

struct __non_trivial{};

template <class Type>
union __variant_storage<Type,__trivial>
{
    Type m_type;

    constexpr __variant_storage() : m_type{}
    {}

    template<class... Args>
    constexpr __variant_storage(in_place_type_t<Type>, Args&&... args) :
        m_type{forward<Args>(args)...}
    {}
};

template <class Type>
union __variant_storage<Type,__non_trivial>
{
    aligned_storage_t<sizeof(Type), alignof(Type)> m_storage;

    constexpr __variant_storage() : m_storage{}
    {}

    template<class... Args>
    __variant_storage(in_place_type_t<Type>, Args&&... args) :
        m_storage{}
    {
        new(&m_storage)Type(forward<Args>(args)...);
    }
};

template <>
union __variant_storage<void,__trivial>
{
    constexpr __variant_storage() = default;
};

template <class Type>
union __variant_storage<Type>
{
    static constexpr bool trivial = is_trivially_destructible_v<Type> || is_same_v<Type,void>;

    __variant_storage<Type, conditional_t<trivial, __trivial, __non_trivial>> m_head;

    constexpr __variant_storage() : m_head{}
    {}

    template <class T,
              class... Args,
              enable_if_t<is_same_v<T,Type>, bool> = true
              >
    constexpr __variant_storage(in_place_type_t<T>, Args&&... args) :
        m_head{in_place_type<T>, forward<Args>(args)...}
    {}

    template <class T, enable_if_t<is_same_v<T,Type> && trivial, bool> = true>
    constexpr T& get()
    {
        return m_head.m_type;
    }

    template <class T, enable_if_t<is_same_v<T,Type> && trivial, bool> = true>
    constexpr const T& get() const
    {
        return m_head.m_type;
    }

    template <class T, enable_if_t<is_same_v<T,Type> && !trivial, bool> = true>
    constexpr T& get()
    {
        return *reinterpret_cast<T*>(&m_head.m_storage);
    }

    template <class T, enable_if_t<is_same_v<T,Type> && !trivial, bool> = true>
    constexpr const T& get() const
    {
        return *reinterpret_cast<const T*>(&m_head.m_storage);
    }
};

template <class Type, class... Types>
union __variant_storage
{
    static constexpr bool trivial = is_trivially_destructible_v<Type> || is_same_v<Type,void>;

    __variant_storage<Type, conditional_t<trivial, __trivial, __non_trivial>> m_head;

    __variant_storage<Types...> m_tail;

    __variant_storage()
    {}

    template <class T,
              class... Args,
              enable_if_t<is_same_v<T,Type>, bool> = true
              >
    constexpr __variant_storage(in_place_type_t<T>, Args&&... args) :
        m_head{in_place_type<T>, forward<Args>(args)...}
    {}

    template <class T,
              class... Args,
              enable_if_t<!is_same_v<T,Type>, bool> = true
              >
    constexpr __variant_storage(in_place_type_t<T>, Args&&... args) :
        m_tail{in_place_type<T>, forward<Args>(args)...}
    {}

    template <class T, enable_if_t<is_same_v<T,Type> && trivial, bool> = true>
    constexpr T& get()
    {
        return m_head.m_type;
    }

    template <class T, enable_if_t<is_same_v<T,Type> && trivial, bool> = true>
    constexpr const T& get() const
    {
        return m_head.m_type;
    }

    template <class T, enable_if_t<is_same_v<T,Type> && !trivial, bool> = true>
    constexpr T& get()
    {
        return *reinterpret_cast<T*>(&m_head.m_storage);
    }

    template <class T, enable_if_t<is_same_v<T,Type> && !trivial, bool> = true>
    constexpr const T& get() const
    {
        return *reinterpret_cast<const T*>(&m_head.m_storage);
    }

    template <class T, enable_if_t<!is_same_v<T,Type>, bool> = true>
    constexpr T& get()
    {
        return m_tail.template get<T>();
    }

    template <class T, enable_if_t<!is_same_v<T,Type>, bool> = true>
    constexpr const T& get() const
    {
        return m_tail.template get<T>();
    }
};

template <class T, class... Types>
struct __variant_index; // undefined

template <class T, class... Types>
constexpr size_t __variant_index_v = __variant_index<T, Types...>::value;

template <class T>
struct __variant_index<T> : integral_constant<size_t, 1> {};

template <class T, class... Types>
struct __variant_index<T, T, Types...> : integral_constant<size_t, 0> {};

template <class T, class U, class... Types>
struct __variant_index<T, U, Types...> : integral_constant<size_t, 1 + __variant_index_v<T, Types...>> {};

// Variant Base Class

template <bool CopyConstructible,
          bool MoveConstructible,
          bool CopyAssignable,
          bool MoveAssignable,
          bool TiviallyDestructible,
          class... Types>
class __variant_base; // undefined

// NonTiviallyDestructible Specialisation

template <class... Types>
class __variant_base<false,false,false,false,false,Types...>
{
public:

    __variant_storage<Types...> m_storage;

protected:

    ptrdiff_t m_index = -1;

    __variant_base(const __variant_base&) = delete;
    __variant_base(__variant_base&&) = delete;
    __variant_base& operator=(const __variant_base&) = delete;
    __variant_base& operator=(__variant_base&&) = delete;

    __variant_base() :
        m_storage{},
        m_index{-1}
    {}

    template <class T, class... Args>
    __variant_base(in_place_type_t<T>, Args&&... args) :
        m_storage{},
        m_index{-1}
    {
        __construct(in_place_type<T>, forward<Args>(args) ...);
    }

    template <class Alloc, class T, class... Args>
    __variant_base(allocator_arg_t, const Alloc& a, in_place_type_t<T>, Args&&... args) :
        m_storage{},
        m_index{-1}
    {
        __construct(allocator_arg_t{}, a, in_place_type<T>, forward<Args>(args) ...);
    }

    ~__variant_base()
    {
        if(m_index >= 0)
            __destroy();
    }

    template <class T,
              class... Args,
              enable_if_t<is_constructible_v<T,Args...>,bool> = true
              >
    void __construct(in_place_type_t<T>, Args&&... args)
    {
        assert(m_index < 0);
        new(&m_storage) decay_t<T>{forward<Args>(args) ...};
        m_index = __variant_index_v<decay_t<T>, Types...>;
    };

    template <class Alloc,
              class T,
              class... Args,
              enable_if_t<is_constructible_v<T,allocator_arg_t,const Alloc&,Args...>,bool> = true
              >
    void __construct(allocator_arg_t, const Alloc& a, in_place_type_t<T>, Args&&... args)
    {
        assert(m_index < 0);
        new(&m_storage) decay_t<T>{allocator_arg_t{}, a, forward<Args>(args) ...};
        m_index = __variant_index_v<decay_t<T>, Types...>;
    };

    template <class Alloc,
              class T,
              class... Args,
              enable_if_t<is_constructible_v<T,Args...,const Alloc&>,bool> = true
              >
    void __construct(allocator_arg_t, const Alloc& a, in_place_type_t<T>, Args&&... args)
    {
        assert(m_index < 0);
        new(&m_storage) decay_t<T>{forward<Args>(args) ..., a};
        m_index = __variant_index_v<decay_t<T>, Types...>;
    };

    template <class Alloc,
              class T,
              class... Args,
              enable_if_t<!is_constructible_v<T,allocator_arg_t,const Alloc&,Args...> &&
                          !is_constructible_v<T,Args...,const Alloc&>,bool> = true
              >
    void __construct(allocator_arg_t, const Alloc& a, in_place_type_t<T>, Args&&... args)
    {
        assert(m_index < 0);
        new(&m_storage) decay_t<T>{forward<Args>(args) ...};
        m_index = __variant_index_v<decay_t<T>, Types...>;
    };

private:

    template<class T>
    void __private_copy(const __variant_base& v)
    {
        __construct(in_place_type<T>, v.m_storage.template get<T>());
    }

    template <class Alloc,
              class T
              >
    void __private_copy(allocator_arg_t, const Alloc& a, const __variant_base& v)
    {
        __construct(allocator_arg_t{}, a, in_place_type<T>, v.m_storage.template get<T>());
    }

protected:

    void __copy(const __variant_base& v)
    {
        assert(v.m_index >= 0);
        assert(v.m_index < sizeof...(Types));
        assert(m_index < 0);
        using function = void(__variant_base::*)(const __variant_base&);
        constexpr function __array[sizeof...(Types)] = {&__variant_base::__private_copy<Types> ...};
        (this->*__array[v.m_index])(v);
    }

    template <class Alloc>
    void __copy(allocator_arg_t, const Alloc& a, const __variant_base& v)
    {
        assert(v.m_index >= 0);
        assert(v.m_index < sizeof...(Types));
        assert(m_index < 0);
        using function = void(__variant_base::*)(allocator_arg_t, const Alloc&, const __variant_base&);
        constexpr function __array[sizeof...(Types)] = {&__variant_base::__private_copy<Alloc,Types> ...};
        (this->*__array[v.m_index])(allocator_arg_t{}, a, v);
    }

private:

    template<class T>
    void __private_move(__variant_base&& v)
    {
        __construct(in_place_type<T>, move(v.m_storage.template get<T>()));
    }

    template <class Alloc,
              class T
              >
    void __private_move(allocator_arg_t, const Alloc& a, __variant_base&& v)
    {
        __construct(allocator_arg_t{}, a, in_place_type<T>, move(v.m_storage.template get<T>()));
    }

protected:

    void __move(__variant_base&& v)
    {
        assert(v.m_index >= 0);
        assert(v.m_index < sizeof...(Types));
        assert(m_index < 0);
        using function = void(__variant_base::*)(__variant_base&&);
        constexpr function __array[sizeof...(Types)] = {&__variant_base::__private_move<Types> ...};
        (this->*__array[v.m_index])(forward<__variant_base>(v));
        v.m_index = -1;
    }

    template <class Alloc>
    void __move(allocator_arg_t, const Alloc& a, __variant_base&& v)
    {
        assert(v.m_index >= 0);
        assert(v.m_index < sizeof...(Types));
        assert(m_index < 0);
        using function = void(__variant_base::*)(allocator_arg_t, const Alloc&, __variant_base&&);
        constexpr function __array[sizeof...(Types)] = {&__variant_base::__private_move<Alloc,Types> ...};
        (this->*__array[v.m_index])(allocator_arg_t{}, a, forward<__variant_base>(v));
        v.m_index = -1;
    }

private:

    template<class T, enable_if_t<is_class_v<decay_t<T>>,bool> = true>
    void __private_destroy()
    {
        assert(m_index >= 0);
        reinterpret_cast<add_pointer_t<T>>(&m_storage)->~T();
        m_index = -1;
    };

    template<class T, enable_if_t<!is_class_v<decay_t<T>>,bool> = false>
    void __private_destroy()
    {
        assert(m_index >= 0);
        m_index = -1;
    };

protected:

    void __destroy()
    {
        assert(m_index >= 0);
        assert(m_index < sizeof...(Types));
        using function = void(__variant_base::*)();
        constexpr function __array[sizeof...(Types)] = {&__variant_base::__private_destroy<Types> ...};
        (this->*__array[m_index])();
    };
};

// TiviallyDestructible Specialisation

template <class... Types>
class __variant_base<false,false,false,false,true,Types...>
{
public:

    __variant_storage<Types...> m_storage;

protected:

    ptrdiff_t m_index = -1;

    __variant_base(const __variant_base&) = delete;
    __variant_base(__variant_base&&) = delete;
    __variant_base& operator=(const __variant_base&) = delete;
    __variant_base& operator=(__variant_base&&) = delete;
    ~__variant_base() = default;

    __variant_base() :
        m_storage{},
        m_index{-1}
    {}

    template <class T, class... Args>
    constexpr __variant_base(in_place_type_t<T>, Args&&... args) :
        m_storage{in_place_type<T>, forward<Args>(args) ...},
        m_index{__variant_index_v<decay_t<T>, Types...>}
    {}

    template <class T, class... Args>
    void __construct(in_place_type_t<T>, Args&&... args)
    {
        assert(m_index < 0);
        new(&m_storage) remove_reference_t<T>{forward<Args>(args) ...};
        m_index = __variant_index_v<decay_t<T>, Types...>;
    };

private:

    template<class T>
    void __private_copy(const __variant_base& v)
    {
        __construct(in_place_type<T>, v.m_storage.template get<T>());
    }

protected:

    void __copy(const __variant_base& v)
    {
        assert(v.m_index >= 0 && v.m_index < sizeof...(Types));
        assert(m_index < 0);
        using function = void(__variant_base::*)(const __variant_base&);
        constexpr function __array[sizeof...(Types)] = {&__variant_base::__private_copy<Types> ...};
        (this->*__array[v.m_index])(v);
    }

    void __move(__variant_base&& v)
    {
        __copy(v);
        v.m_index = -1;
    }

    void __destroy()
    {
        assert(m_index >= 0);
        m_index = -1;
    };
};

// MoveAssignable Specialisation

template <bool TiviallyDestructible,
          class... Types>
class __variant_base<false,false,false,true,TiviallyDestructible,Types...> :
public __variant_base<false,false,false,false,TiviallyDestructible,Types...>
{
    using __base = __variant_base<false,false,false,false,TiviallyDestructible,Types...>;

protected:

    using __base::__base;
    using __base::__move;
    using __base::__destroy;
    using __base::m_index;

    __variant_base& operator=(__variant_base&& rhs) noexcept(conjunction_v<is_nothrow_move_constructible<Types> ...> &&
                                                             conjunction_v<is_nothrow_move_assignable<Types> ...>)
    {
        static_assert(conjunction_v<is_move_constructible<Types> ...> &&
                      conjunction_v<is_move_assignable   <Types> ...> ,
        R"(This function shall not participate in overload resolution unless is_move_constructible_v<Ti> &&
                                                                             is_move_assignable_v<Ti> is true for all i.)");
        if(!(m_index < 0))
            __destroy();
        if(!(rhs.m_index < 0))
            __move(move(rhs));
        return *this;
    }
};

// CopyAssignable Specialisation

template <bool MoveAssignable,
          bool TiviallyDestructible,
          class... Types>
class __variant_base<false,false,true,MoveAssignable,TiviallyDestructible,Types...> :
public __variant_base<false,false,false,MoveAssignable,TiviallyDestructible,Types...>
{
    using __base = __variant_base<false,false,false,MoveAssignable,TiviallyDestructible,Types...>;

protected:

    using __base::__base;
    using __base::__copy;
    using __base::__destroy;
    using __base::m_index;

    __variant_base& operator=(const __variant_base& rhs)
    {
        static_assert(conjunction_v<is_copy_constructible<Types> ...> &&
                      conjunction_v<is_move_constructible<Types> ...> &&
                      conjunction_v<is_copy_assignable   <Types> ...> ,
        R"(This function shall not participate in overload resolution unless is_copy_constructible_v<Ti> &&
                                                                             is_move_constructible_v<Ti> &&
                                                                             is_copy_assignable_v<Ti> is true for all i.)");
        if(!(m_index < 0))
            __destroy();
        if(!(rhs.m_index < 0))
            __copy(rhs);
        return *this;
    }

    __variant_base& operator=(__variant_base&&) = default;
};

// MoveConstructible Specialisation

template <bool CopyAssignable,
          bool MoveAssignable,
          bool TiviallyDestructible,
          class... Types>
class __variant_base<false,true,CopyAssignable,MoveAssignable,TiviallyDestructible,Types...> :
public __variant_base<false,false,CopyAssignable,MoveAssignable,TiviallyDestructible,Types...>
{
    using __base = __variant_base<false,false,CopyAssignable,MoveAssignable,TiviallyDestructible,Types...>;

protected:

    using __base::__base;
    using __base::__move;

    __variant_base(__variant_base&& v) :
        __base{}
    {
        static_assert(conjunction_v<is_copy_constructible<Types> ...>,
            "This function shall not participate in overload resolution unless is_copy_constructible_v<Ti> is true for all i.");
        if(!(v.m_index < 0))
        {
            __move(v);
            v.m_index = -1;
        }
    }

    __variant_base& operator=(const __variant_base&) = default;
    __variant_base& operator=(__variant_base&&) = default;
};

// CopyConstructible Specialisation

template <bool MoveConstructible,
          bool CopyAssignable,
          bool MoveAssignable,
          bool TiviallyDestructible,
          class... Types>
class __variant_base<true,MoveConstructible,CopyAssignable,MoveAssignable,TiviallyDestructible,Types...> :
public __variant_base<false,MoveConstructible,CopyAssignable,MoveAssignable,TiviallyDestructible,Types...>
{
    using __base = __variant_base<false,MoveConstructible,CopyAssignable,MoveAssignable,TiviallyDestructible,Types...>;

protected:

    using __base::__base;
    using __base::__copy;

    __variant_base(const __variant_base& v) :
        __base{}
    {
        static_assert(conjunction_v<is_move_constructible<Types> ...>,
            "This function shall not participate in overload resolution unless is_move_constructible_v<Ti> is true for all i.");
        if(!(v.m_index < 0))
            __copy(v);
    }

    __variant_base& operator=(const __variant_base&) = default;
    __variant_base& operator=(__variant_base&&) = default;
};

template < template <class> class Test, class... Types>
struct __first_or_last;

template < template <class> class Test, class... Types>
using __first_or_last_t = typename __first_or_last<Test, Types...>::type;

template < template <class> class Test, class T>
struct __first_or_last<Test,T> {using type = T;};

template < template <class> class Test, class T, class... Types>
struct __first_or_last<Test, T, Types...>
{
    static constexpr Test<T> test;
    using type = conditional_t<!test, T, __first_or_last_t<Test, Types...>>;
};

template <typename T>
struct __argument {using type = T;};

template <typename... Ts>
struct __imaginary_function; // undefined

template <>
struct __imaginary_function<> {constexpr void operator()() const noexcept;};

template <typename... Ts>
struct __imaginary_function<void, Ts...> : __imaginary_function<Ts...>
{
    using __imaginary_function<Ts...>::operator();
    constexpr __argument<void> operator()() const noexcept;
};

template <typename T, typename... Ts>
struct __imaginary_function<T, Ts...> : __imaginary_function<Ts...>
{
    using __imaginary_function<Ts...>::operator();
    constexpr __argument<T> operator()(T) const noexcept;
};

template <class T, class... Types>
using __imaginary_function_argument_t = typename result_of_t<__imaginary_function<Types...>(T)>::type;

template <class T, class... Types>
struct __count; // undefined

template <class T, class... Types>
constexpr size_t __count_v = __count<T, Types...>::value;

template <class T,class U>
struct __count<T,U> : integral_constant<size_t, is_same_v<T,U >> {};

template <class T, class U, class... Types>
struct __count<T, U, Types...> : integral_constant<size_t, is_same_v<T,U > + __count_v<T, Types...>> {};

template <class T, class... Types>
constexpr bool __imaginary_function_well_formed_v = __count<T, Types...>::value == 1;

// 20.7.2, variant of value types
template <class... Types>
class variant;

// 20.7.3, variant helper classes
template <class T> struct variant_size; // undefined
template <class T> struct variant_size<const T>;
template <class T> struct variant_size<volatile T>;
template <class T> struct variant_size<const volatile T>;

template <class T> constexpr size_t variant_size_v = variant_size<T>::value;

template <class... Types>
struct variant_size<variant<Types...>> : integral_constant<size_t, sizeof...(Types)> {};

template <size_t I, class T> struct variant_alternative; // undefined
template <size_t I, class T> struct variant_alternative<I, const T>;
template <size_t I, class T> struct variant_alternative<I, volatile T>;
template <size_t I, class T> struct variant_alternative<I, const volatile T>;

template <size_t I, class T>
using variant_alternative_t = typename variant_alternative<I, T>::type;

template <size_t I, class... Types>
struct variant_alternative<I, variant<Types...>>
{
    static_assert(I < sizeof...(Types), "variant_alternative index out of range");
    using type = tuple_element_t<I, tuple<Types...>>;
};

constexpr size_t variant_npos = -1;

// 20.7.10, class bad_variant_access
class bad_variant_access : logic_error {
public:
    bad_variant_access() : logic_error{"bad variant access"} {};
};

// 20.7.4, value access
template <class T, class... Types>
inline
constexpr bool holds_alternative(const variant<Types...>& v) noexcept
{
    return __variant_index_v<T, Types...> == v.index();
};

template <size_t I, class... Types>
inline
constexpr variant_alternative_t<I, variant<Types...>>&
get(variant<Types...>& v)
{
    using T = variant_alternative_t<I,variant<Types...>>;
    return get<T>(v);
};

template <size_t I, class... Types>
inline
constexpr variant_alternative_t<I, variant<Types...>>&&
get(variant<Types...>&& v)
{
    using T = variant_alternative_t<I,variant<Types...>>;
    return move(get<T>(v));
};

template <size_t I, class... Types>
inline
constexpr variant_alternative_t<I, variant<Types...>> const&
get(const variant<Types...>& v)
{
    using T = variant_alternative_t<I,variant<Types...>>;
    return get<T>(v);
};

template <size_t I, class... Types>
inline
constexpr variant_alternative_t<I, variant<Types...>> const&&
get(const variant<Types...>&& v)
{
    using T = variant_alternative_t<I,variant<Types...>>;
    return move(get<T>(v));
};

template <class T, class... Types>
inline
constexpr T&
get(variant<Types...>& v)
{
    if(holds_alternative<T>(v))
    return v.m_storage.template get<T>();
    throw bad_variant_access{};
};

template <class T, class... Types>
inline
constexpr T&&
get(variant<Types...>&& v)
{
    if(holds_alternative<T>(v))
    return v.m_storage.template get<T>();
    throw bad_variant_access{};
};

template <class T, class... Types>
inline
constexpr const T&
get(const variant<Types...>& v)
{
    if(holds_alternative<T>(v))
    return v.m_storage.template get<T>();
    throw bad_variant_access{};
};

template <class T, class... Types>
inline
constexpr const T&&
get(const variant<Types...>&& v)
{
    if(holds_alternative<T>(v))
    return v.m_storage.template get<T>();
    throw bad_variant_access{};
};

template <size_t I, class... Types>
inline
constexpr add_pointer_t<variant_alternative_t<I, variant<Types...>>>
get_if(variant<Types...>* v) noexcept
{
    using T = variant_alternative_t<I,variant<Types...>>;
    return get_if<T>(v);
};

template <size_t I, class... Types>
inline
constexpr add_pointer_t<const variant_alternative_t<I, variant<Types...>>>
get_if(const variant<Types...>* v) noexcept
{
    using T = variant_alternative_t<I,variant<Types...>>;
    return get_if<T>(v);
};

template <class T, class... Types>
inline
constexpr add_pointer_t<T>
get_if(variant<Types...>* v) noexcept
{
    if(holds_alternative<T>(*v))
    return &(v->m_storage.template get<T>());
    return nullptr;
};

template <class T, class... Types>
inline
constexpr add_pointer_t<const T>
get_if(const variant<Types...>* v) noexcept
{
    if(holds_alternative<T>(*v))
    return &(v->m_storage.template get<T>());
    return nullptr;
};

template <class... Types>
using __comparison_function_type = bool(*)(const variant<Types...>&, const variant<Types...>&);

template <size_t I, class... Types>
constexpr bool __variant_equal_to(const variant<Types...>& v, const variant<Types...>& w)
{
    return get<I>(v) == get<I>(w);
}

template <class... Types, size_t... I>
constexpr array<__comparison_function_type<Types...>, sizeof...(I)> __make_equal_to_array(index_sequence<I...>)
{
    return { __variant_equal_to<I, Types...> ... };
}

template <size_t I, class... Types>
constexpr bool __variant_less(const variant<Types...>& v, const variant<Types...>& w)
{
    return get<I>(v) < get<I>(w);
}

template <class... Types, size_t... I>
constexpr array<__comparison_function_type<Types...>, sizeof...(I)> __make_less_array(index_sequence<I...>)
{
    return { __variant_less<I, Types...> ... };
}

template <class Visitor, class... Variants>
using __invoker_function_type = auto(*)(Visitor&&, Variants&&...) -> result_of_t<Visitor(variant_alternative_t<0, decay_t<Variants>> ...)>;

template <size_t I, class Visitor, class... Variants>
auto __alternative_invoker(Visitor&& vis, Variants&&... vars)
{
    return invoke(forward<Visitor>(vis), get<I>(forward<Variants>(vars)) ...);
}

template <class Visitor, class... Variants, size_t... I>
constexpr array<__invoker_function_type<Visitor, Variants...>, sizeof...(I)> __make_invoker_array(index_sequence<I...>)
{
    return { __alternative_invoker<I, Visitor, Variants...> ... };
}

template <class Visitor, class... Types, class... Variants>
auto __variant_invoke(Visitor&& vis, variant<Types...>& var, Variants&&... vars)
{
    constexpr auto __array = __make_invoker_array<Visitor, variant<Types...>, Variants...>(index_sequence_for<Types...>{});
    return __array[var.index()](forward<Visitor>(vis), forward<variant<Types...>>(var), forward<Variants>(vars) ...);
}

template <class... Types>
using __swap_function_type = void(*)(variant<Types...>&, variant<Types...>&);

template <size_t I, class... Types>
constexpr void __swap(variant<Types...>& v, variant<Types...>& w) noexcept
{
    swap(get<I>(v), get<I>(w));
}

template <class... Types, size_t... I>
constexpr array<__swap_function_type<Types...>, sizeof...(I)> __make_swap_array(index_sequence<I...>)
{
    return { __swap<I, Types...> ... };
}

template <class... Types>
using __hash_function_type = size_t(*)(const variant<Types...>&);

template <size_t I, class... Types>
constexpr size_t __hash(const variant<Types...>& v)
{
    using T = variant_alternative_t<I,variant<Types...>>;
    return hash<T>{}(get<I>(v));
}

template <class... Types, size_t... I>
constexpr array<__hash_function_type<Types...>, sizeof...(I)> __make_hash_array(index_sequence<I...>)
{
    return { __hash<I, Types...> ... };
}

// 20.7.5, relational operators
template <class... Types>
inline
constexpr bool operator==(const variant<Types...>& v, const variant<Types...>& w)
{
    constexpr auto __variant_equal_to = __make_equal_to_array<Types...>(index_sequence_for<Types...>{});
    return (v.valueless_by_exception() && w.valueless_by_exception()) || (v.index() == w.index() && __variant_equal_to[v.index()](v,w));
};

template <class... Types>
inline
constexpr bool operator!=(const variant<Types...>& v, const variant<Types...>& w)
{
    return !(v == w);
};

template <class... Types>
inline
constexpr bool operator<(const variant<Types...>& v, const variant<Types...>& w)
{
    constexpr auto __variant_less = __make_less_array<Types...>(index_sequence_for<Types...>{});
    return (v.index() < w.index()) || (v.index() == w.index() && !v.valueless_by_exception() && __variant_less[v.index()](v,w));
};

template <class... Types>
inline
constexpr bool operator>(const variant<Types...>& v, const variant<Types...>& w)
{
    return w < v;
}

template <class... Types>
constexpr bool operator<=(const variant<Types...>& v, const variant<Types...>& w)
{
    return !(v > w);
}

template <class... Types>
inline
constexpr bool operator>=(const variant<Types...>& v, const variant<Types...>& w)
{
    return !(v < w);
}

// 20.7.6, visitation
template <class Visitor, class... Variants>
inline
constexpr auto visit(Visitor&& vis, Variants&&... vars)
{
    return __variant_invoke(forward<Visitor>(vis), forward<Variants>(vars) ...);
};

// 20.7.7, class monostate
struct monostate {};

// 20.7.8, monostate relational operators
inline
constexpr bool operator<(monostate, monostate) noexcept {return false;};
inline
constexpr bool operator>(monostate, monostate) noexcept {return false;};
inline
constexpr bool operator<=(monostate, monostate) noexcept {return true;};
inline
constexpr bool operator>=(monostate, monostate) noexcept {return true;};
inline
constexpr bool operator==(monostate, monostate) noexcept {return true;};
inline
constexpr bool operator!=(monostate, monostate) noexcept {return false;};

// 20.7.9, specialized algorithms
template <class... Types>
inline
void swap(variant<Types...>& lhs, variant<Types...>& rhs) noexcept(conjunction_v<is_nothrow_move_constructible<Types> ...> &&
                                                                   conjunction_v<is_nothrow_swappable<Types> ...>)
{
    lhs.swap(rhs);
};

template <class... Types>
class variant : public __variant_base<conjunction_v<is_copy_constructible<Types>...>,
                                                   conjunction_v<is_move_constructible<Types>...>,
                                                   conjunction_v<is_copy_assignable<Types>...>,
                                                   conjunction_v<is_move_assignable<Types>...>,
                                                   conjunction_v<is_trivially_destructible<Types>...>,
                                                   Types...>
{
    using __base = __variant_base<conjunction_v<is_copy_constructible<Types>...>,
                                               conjunction_v<is_move_constructible<Types>...>,
                                               conjunction_v<is_copy_assignable<Types>...>,
                                               conjunction_v<is_move_assignable<Types>...>,
                                               conjunction_v<is_trivially_destructible<Types>...>,
                                               Types...>;
    using __base::__copy;
    using __base::__move;
    using __base::__construct;
    using __base::__destroy;
    using __base::m_index;

public:

    // 20.7.2.1, constructors

    template <class T0 = variant_alternative_t<0,variant>,
              enable_if_t<is_default_constructible_v<T0>, bool> = true>
    inline
    constexpr variant() noexcept(is_nothrow_default_constructible_v<T0>) :
        __base{in_place_type<T0>}
    {
        static_assert(is_default_constructible_v<T0>,
            "This function shall not participate in overload resolution unless is_default_constructible_v<T0> is true.");
    };

    template <class T0 = variant_alternative_t<0,variant>,
              enable_if_t<!is_default_constructible_v<T0>, bool> = false
              >
    inline
    constexpr variant() noexcept(is_nothrow_default_constructible_v<T0>) = delete;

    // We'll inherit the copy and move constructors from the __base

    inline
    variant(const variant&) = default;

    inline
    variant(variant&&) = default;

    template <class T,
              class Tj = __imaginary_function_argument_t<T,Types...>,
              enable_if_t<__imaginary_function_well_formed_v<Tj,Types...>,bool> = true,
              enable_if_t<!is_same_v<decay_t<T>,variant>,bool> = false,
              enable_if_t<is_constructible_v<Tj,T>,bool> = true
              >
    inline
    constexpr variant(T&& t) noexcept(is_nothrow_constructible_v<Tj,T>) :
        __base{in_place_type<Tj>, forward<T>(t)}
    {
        static_assert(!is_same_v<decay_t<T>,variant> && is_constructible_v<Tj,T> && __imaginary_function_well_formed_v<Tj,Types...>,
            R"(This function shall not participate in overload resolution
               unless is_same_v<decay_t<T>, variant> is false, unless is_constructible_v<Tj, T> is true, and
               unless the expression FUN(std::forward<T>(t)) (with FUN being the above-mentioned set of imaginary functions) is well formed.)");
    };

    template <class T,
              class... Args,
              enable_if_t<is_constructible_v<T, Args...>, bool> = true
              >
    inline
    constexpr explicit variant(in_place_type_t<T>, Args&&... args) :
        __base{in_place_type<T>, forward<Args>(args)...}
    {};

    template <class T,
              class U,
              class... Args,
              enable_if_t<is_constructible_v<T, initializer_list<U>&, Args...>, bool> = true
              >
    inline
    constexpr explicit variant(in_place_type_t<T>, initializer_list<U> il, Args&&... args) :
        __base{in_place_type<T>, forward<initializer_list<U>>(il), forward<Args>(args)...}
    {};

    template <size_t I,
              class... Args,
              class T = variant_alternative_t<I,variant>,
              enable_if_t<is_constructible_v<T, Args...>, bool> = true
              >
    inline
    constexpr explicit variant(in_place_index_t<I>, Args&&... args) :
        __base{in_place_type<T>, forward<Args>(args)...}
    {};

    template <size_t I,
              class U,
              class... Args,
              class T = variant_alternative_t<I,variant>,
              enable_if_t<is_constructible_v<T, initializer_list<U>&, Args...>, bool> = true
              >
    inline
    constexpr explicit variant(in_place_index_t<I>, initializer_list<U> il, Args&&... args) :
        __base{in_place_type<variant_alternative_t<I,variant>>, forward<initializer_list<U>>(il), forward<Args>(args)...}
    {};

    // allocator-extended constructors
    template <class Alloc,
              class T0 = variant_alternative_t<0,variant>,
              enable_if_t<is_constructible_v<T0>, bool> = true>
    inline
    variant(allocator_arg_t, const Alloc& a) :
        __base{allocator_arg_t{}, a, in_place_type<T0>}
    {
        static_assert(is_default_constructible_v<T0>,
            "This function shall not participate in overload resolution unless is_default_constructible_v<T0> is true.");
    };

    template <class Alloc,
              class TN = __first_or_last_t<is_copy_constructible,Types...>,
              enable_if_t<is_copy_constructible_v<TN>, bool> = true
              >
    inline
    variant(allocator_arg_t, const Alloc& a, const variant& v) :
        __base{}
    {
        static_assert(conjunction_v<is_copy_constructible<Types> ...>,
            "This function shall not participate in overload resolution unless is_copy_constructible_v<Ti> is true for all i.");
        if(!v.valueless_by_exception())
            __copy(allocator_arg_t{}, a, v);
    }

    template <class Alloc,
              class TN = __first_or_last_t<is_move_constructible,Types...>,
              enable_if_t<is_move_constructible_v<TN>, bool> = true
              >
    inline
    variant(allocator_arg_t, const Alloc& a, variant&& v) :
        __base{}
    {
        static_assert(conjunction_v<is_move_constructible<Types> ...>,
            "This function shall not participate in overload resolution unless is_move_constructible_v<Ti> is true for all i.");
        if(!v.valueless_by_exception())
            __move(allocator_arg_t{}, a, forward<variant>(v));
    }

    template <class Alloc,
              class T,
              class Tj = __imaginary_function_argument_t<T,Types...>,
              enable_if_t<!is_same_v<decay_t<T>,variant>,bool> = false,
              enable_if_t<is_constructible_v<Tj,T>,bool> = true,
              enable_if_t<__imaginary_function_well_formed_v<Tj,Types...>,bool> = true
              >
    inline
    variant(allocator_arg_t, const Alloc& a, T&& t) :
        __base{allocator_arg_t{}, a, in_place_type<T>, forward<T>(t)}
    {
        static_assert(!is_same_v<decay_t<T>,variant> && is_constructible_v<Tj,T> && __imaginary_function_well_formed_v<Tj,Types...>,
            R"(This function shall not participate in overload resolution unless is_same_v<decay_t<T>, variant> is false,
              unless is_constructible_v<Tj, T> is true, and
              unless the expression FUN( std::forward<T>(t)) (with FUN being the above-mentioned set of imaginary functions) is well formed.)");
    };

    template <class Alloc,
              class T,
              class... Args,
              enable_if_t<is_constructible_v<T, Args...>, bool> = true
              >
    inline
    variant(allocator_arg_t, const Alloc& a, in_place_type_t<T>, Args&&... args) :
        __base{allocator_arg_t{}, a, in_place_type<T>, forward<Args>(args) ...}
    {};

    template <class Alloc,
              class T,
              class U,
              class... Args,
              enable_if_t<is_constructible_v<T, initializer_list<U>&, Args...>, bool> = true
              >
    inline
    variant(allocator_arg_t, const Alloc& a, in_place_type_t<T>, initializer_list<U> il, Args&&... args) :
        __base{allocator_arg_t{}, a, in_place_type<T>, forward<initializer_list<U>>(il), forward<Args>(args) ...}
    {};

    template <class Alloc,
              size_t I,
              class... Args,
              class T = variant_alternative_t<I,variant>,
              enable_if_t<is_constructible_v<T, Args...>, bool> = true
              >
    inline
    variant(allocator_arg_t, const Alloc& a, in_place_index_t<I>, Args&&... args) :
        __base{allocator_arg_t{}, a, in_place_type<T>, forward<Args>(args) ...}
    {};

    template <class Alloc,
              size_t I,
              class U,
              class... Args,
              class T = variant_alternative_t<I,variant>,
              enable_if_t<is_constructible_v<T, initializer_list<U>&, Args...>, bool> = true
              >
    inline
    variant(allocator_arg_t, const Alloc& a, in_place_index_t<I>, initializer_list<U> il, Args&&... args) :
        __base{allocator_arg_t{}, a, in_place_type<T>, forward<initializer_list<U>>(il), forward<Args>(args) ...}
    {};

    // 20.7.2.2, destructor
    inline
    ~variant() = default;

    // 20.7.2.3, assignment
    inline
    variant& operator=(const variant&) = default;

    inline
    variant& operator=(variant&&) = default;

    template <class T,
              class Tj = __imaginary_function_argument_t<T,Types...>,
              enable_if_t<!is_same_v<decay_t<T>,variant>,bool> = false,
              enable_if_t<is_assignable_v<Tj&,T>,bool> = true,
              enable_if_t<is_constructible_v<Tj,T>,bool> = true,
              enable_if_t<__imaginary_function_well_formed_v<Tj,Types...>,bool> = true
              >
    inline
    variant& operator=(T&& rhs) noexcept(conjunction_v<is_nothrow_assignable<Types&,Types>    ...>  &&
                                         conjunction_v<is_nothrow_constructible<Types&,Types> ...>)
    {
        static_assert(!is_same_v<decay_t<T>, variant> && is_assignable_v<Tj&, T> && is_constructible_v<Tj, T>,
            R"(This function shall not participate in overload resolution unless is_same_v<decay_t<T>, variant> is false,
               unless is_assignable_v<Tj&, T> && is_constructible_v<Tj, T> is true, and
               unless the expression FUN (std::forward<T>(t)) (with FUN being the above-mentioned set of imaginary functions) is well formed.)");
        if(!valueless_by_exception())
            __destroy();
        __construct(in_place_type<T>, forward<T>(rhs));
        return *this;
    };

    // 20.7.2.4, modifiers

    template <class T, class... Args>
    inline
    void emplace(Args&&... args)
    {
        if(!valueless_by_exception())
            __destroy();
        __construct(in_place_type<T>, forward<Args>(args)...);
    };

    template <class T, class U, class... Args>
    inline
    void emplace(initializer_list<U> il, Args&&... args)
    {
        if(!valueless_by_exception())
            __destroy();
        __construct(in_place_type<T>, il, forward<Args>(args)...);
    };

    template <size_t I, class... Args>
    inline
    void emplace(Args&&... args)
    {
        using T = variant_alternative_t<I,variant>;
        emplace<T>(forward<Args>(args)...);
    };

    template <size_t I, class U, class... Args>
    inline
    void emplace(initializer_list<U> il, Args&&... args)
    {
        using T = variant_alternative_t<I,variant>;
        emplace<T>(il, forward<Args>(args)...);
    };

    // 20.7.2.5, value status
    inline
    constexpr bool valueless_by_exception() const noexcept
    {
        return m_index == variant_npos;
    }

    inline
    constexpr size_t index() const noexcept
    {
        return m_index;
    };

    // 20.7.2.6, swap
    inline
    void swap(variant& rhs) noexcept(conjunction_v<is_nothrow_move_constructible<Types> ...> &&
                                     conjunction_v<is_nothrow_swappable<Types> ...>)
    {
        constexpr auto __swap = __make_swap_array<Types...>(index_sequence_for<Types...>{});
        variant& lhs = *this;
        if(lhs.valueless_by_exception() && rhs.valueless_by_exception())
            return;
        if(lhs.m_index == rhs.m_index)
            __swap[lhs.m_index](lhs,rhs);
        else
        {
            variant tmp{rhs};
            rhs.m_index = lhs.m_index;
            __swap[lhs.m_index](rhs,lhs);
            lhs.m_index = tmp.m_index;
            __swap[lhs.m_index](lhs,tmp);
        }
    }
};

// 20.7.11, hash support
// template <class T> struct hash;
template <class... Types>
struct hash<variant<Types...>>
{
    inline
    size_t operator()(const variant<Types...>& v) noexcept
    {
        constexpr auto hash = __make_hash_array<Types...>(index_sequence_for<Types...>{});
        return hash[v.index()](v);
    }
};

template <>
struct hash<monostate>
{
    inline
    size_t operator()(monostate) noexcept
    {
        return 42;
    }
};

// 20.7.12, allocator-related traits
// template <class T, class Alloc> struct uses_allocator;

template <class... Types, class Alloc>
struct uses_allocator<variant<Types...>, Alloc> : true_type {};

} // namespace std
