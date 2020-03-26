#include <iostream>
#include <vector>
#include <typeinfo>
#include <cstring>

using namespace std;

class Unit
{
public:
    using Flags = unsigned int;
public:
    virtual ~Unit() = default;

    virtual void add(const shared_ptr< Unit >&, Flags)
    {
        throw runtime_error("Not supported");
    }

    virtual string compile(unsigned int level = 0) const = 0;

protected:

    virtual string generateShift(unsigned int level) const
    {
        static const auto DEFAULT_SHIFT = "    ";
        string result;

        for (unsigned int i = 0; i < level; ++i)
            result += DEFAULT_SHIFT;

        return result;
    }
};


class cpp_ClassUnit : public Unit
{
public:
    enum AccessModifier
    {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };

    static const vector< string > ACCESS_MODIFIERS;

public:

    explicit cpp_ClassUnit(const string& name) : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }

    void add(const shared_ptr< Unit >& unit, Flags flags)
    {
        int accessModifier = PRIVATE;

        if (flags < ACCESS_MODIFIERS.size())
            accessModifier = flags;

        m_fields[accessModifier].push_back(unit);
    }

    string compile(unsigned int level = 0) const
    {
        string result = generateShift(level) + "class " + m_name + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i)
        {
            if (m_fields[i].empty())
                continue;

            result += ACCESS_MODIFIERS[i] + ":\n";
            for (const auto& f : m_fields[i])
            {
                result += f->compile(level + 1);
            }
            result += "\n";
        }

        result += generateShift(level) + "};\n";

        return result;
    }

private:
    string m_name;
    using Fields = vector< shared_ptr< Unit > >;
    vector< Fields > m_fields;
};

const vector< string > cpp_ClassUnit::ACCESS_MODIFIERS = { "public", "protected", "private" };




class cpp_MethodUnit : public Unit
{
public:
    enum Modifier
    {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2,
        DEFAULT = 1 << 3
    };
public:

    cpp_MethodUnit(const string& name,
        const string& returnType,
        Flags flags, int arg_num = 0, ...) :
        m_name(name),
        m_returnType(returnType),
        m_flags(flags)
    {
        if (arg_num > 0)
        {
            va_list argptr;
            __crt_va_start(argptr, arg_num);

            for (; arg_num; --arg_num)
            {
                m_args.push_back(__crt_va_arg(argptr, const char*));
            }
            __crt_va_end(argptr);
        }
    }

    void add(const shared_ptr< Unit >& unit, Flags /* flags */ = 0)
    {
        m_body.push_back(unit);
    }

    string compile(unsigned int level = 0) const
    {
        string result = generateShift(level);

        if (m_flags & STATIC)
        {
            result += "static ";
        }
        else if (m_flags & VIRTUAL)
        {
            result += "virtual ";
        }

        result += m_returnType + " ";
        result += m_name + "(";

        {
            size_t size = m_args.size();
            for (size_t i = 0; i < size; ++i)
            {
                result += m_args[i];
                if (i < size - 1)
                    result += ", ";
            }
        }

        result += ")";

        if (m_flags & CONST)
        {
            result += " const";
        }

        result += " {\n";

        for (const auto& b : m_body)
        {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }

private:

    string m_name;
    string m_returnType;
    Flags m_flags;
    vector< shared_ptr< Unit > > m_body;
    vector< string > m_args;
};

class cpp_PrintOperatorUnit : public Unit
{
public:
    explicit cpp_PrintOperatorUnit(const string& text) :
        m_text(text)
    {}
    string compile(unsigned int level = 0) const
    {
        return generateShift(level) + "printf( \"" + m_text +
            "\" );\n";
    }
private:
    string m_text;
};

class CodeGenerator
{
public:
    explicit CodeGenerator() {};

    virtual Unit* getClassCode(string class_name) const = 0;

private:


};

class CppCodeGenerator : CodeGenerator
{

public:
    explicit CppCodeGenerator() {}

    Unit* getClassCode(string class_name = "MyClass") const override final
    {
        cpp_ClassUnit* Class = new cpp_ClassUnit(class_name);

        Class->add(
            make_shared< cpp_MethodUnit >("testFunc1", "void", 0),
            cpp_ClassUnit::PUBLIC
        );

        Class->add(
            make_shared< cpp_MethodUnit >("testFunc2", "void",
                cpp_MethodUnit::STATIC),
            cpp_ClassUnit::PRIVATE
        );

        Class->add(
            make_shared< cpp_MethodUnit >("testFunc3", "void",
                cpp_MethodUnit::VIRTUAL | cpp_MethodUnit::CONST, 3, "int", "double", "UserType"),
            cpp_ClassUnit::PUBLIC
        );

        auto method = make_shared< cpp_MethodUnit >("testFunc4",
            "void", cpp_MethodUnit::STATIC);

        method->add(make_shared< cpp_PrintOperatorUnit >("Hello, world!"));
        Class->add(method, cpp_ClassUnit::PROTECTED);

        return Class;
    }

};

class java_ClassUnit : public Unit
{
public:
    enum AccessModifier
    {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };

    static const vector< string > ACCESS_MODIFIERS;

public:

    explicit java_ClassUnit(const string& name) : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }

    void add(const shared_ptr< Unit >& unit, Flags flags)
    {
        int accessModifier = PRIVATE;

        if (flags < ACCESS_MODIFIERS.size())
            accessModifier = flags;

        m_fields[accessModifier].push_back(unit);
    }

    string compile(unsigned int level = 0) const
    {
        string result = generateShift(level) + "class " + m_name + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i)
        {
            if (m_fields[i].empty())
                continue;

            //result += ACCESS_MODIFIERS[i] + ":\n";
            for (const auto& f : m_fields[i])
            {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " " + f->compile(0);
            }
            result += "\n";
        }

        result += generateShift(level) + "};\n";

        return result;
    }

private:
    string m_name;
    using Fields = vector< shared_ptr< Unit > >;
    vector< Fields > m_fields;
};

const vector< string > java_ClassUnit::ACCESS_MODIFIERS = { "public", "protected", "private" };

class java_MethodUnit : public Unit
{
public:
    enum Modifier
    {
        STATIC = 1,
        //CONST = 1 << 1,
        //VIRTUAL = 1 << 2,
        DEFAULT = 1 << 3
    };
public:

    java_MethodUnit(const string& name,
        const string& returnType,
        Flags flags, int arg_num = 0, ...) :
        m_name(name),
        m_returnType(returnType),
        m_flags(flags)
    {
        if (arg_num > 0)
        {
            va_list argptr;
            __crt_va_start(argptr, arg_num);

            for (; arg_num; --arg_num)
            {
                m_args.push_back(__crt_va_arg(argptr, const char*));
            }
            __crt_va_end(argptr);
        }
    }

    void add(const shared_ptr< Unit >& unit, Flags /* flags */ = 0)
    {
        m_body.push_back(unit);
    }

    string compile(unsigned int level = 0) const
    {
        string result = generateShift(level);

        if (m_flags & STATIC)
        {
            result += "static ";
        }
        //else if (m_flags & VIRTUAL)
        //{
        //    result += "virtual ";
        //}

        result += m_returnType + " ";
        result += m_name + "(";

        {
            size_t size = m_args.size();
            for (size_t i = 0; i < size; ++i)
            {
                result += m_args[i];
                if (i < size - 1)
                    result += ", ";
            }
        }

        result += ")";

        //if (m_flags & CONST)
        //{
        //    result += " const";
        //}

        result += " {\n";

        for (const auto& b : m_body)
        {
            result += b->compile(level + 2);
        }

        result += generateShift(level + 1) + "}\n";

        return result;
    }

private:

    string m_name;
    string m_returnType;
    Flags m_flags;
    vector< shared_ptr< Unit > > m_body;
    vector< string > m_args;
};

class java_PrintOperatorUnit : public Unit
{
public:
    explicit java_PrintOperatorUnit(const string& text) :
        m_text(text)
    {}
    string compile(unsigned int level = 0) const
    {
        return generateShift(level) + "System.out.println( \"" + m_text +
            "\" );\n";
    }
private:
    string m_text;
};

class JavaCodeGenerator : CodeGenerator
{

public:
    explicit JavaCodeGenerator() {}

    Unit* getClassCode(string class_name = "MyClass") const override final
    {
        java_ClassUnit* Class = new java_ClassUnit(class_name);

        Class->add(
            make_shared< java_MethodUnit >("testFunc1", "void", 0),
            java_ClassUnit::PUBLIC
        );

        Class->add(
            make_shared< java_MethodUnit >("testFunc2", "void",
                java_MethodUnit::STATIC),
            java_ClassUnit::PRIVATE
        );

        Class->add(
            make_shared< java_MethodUnit >("testFunc3", "void",
                java_MethodUnit::DEFAULT, 3, "int", "double", "UserType"),
            java_ClassUnit::PUBLIC
        );

        auto method = make_shared< java_MethodUnit >("testFunc4",
            "void", java_MethodUnit::STATIC);

        method->add(make_shared< java_PrintOperatorUnit >("Hello, world!"));
        Class->add(method, java_ClassUnit::PROTECTED);

        return Class;
    }

};


class cs_ClassUnit : public Unit
{
public:
    enum AccessModifier
    {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };

    static const vector< string > ACCESS_MODIFIERS;

public:

    explicit cs_ClassUnit(const string& name) : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }

    void add(const shared_ptr< Unit >& unit, Flags flags)
    {
        int accessModifier = PRIVATE;

        if (flags < ACCESS_MODIFIERS.size())
            accessModifier = flags;

        m_fields[accessModifier].push_back(unit);
    }

    string compile(unsigned int level = 0) const
    {
        string result = generateShift(level) + "class " + m_name + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i)
        {
            if (m_fields[i].empty())
                continue;

            //result += ACCESS_MODIFIERS[i] + ":\n";
            for (const auto& f : m_fields[i])
            {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " " + f->compile(0);
            }
            result += "\n";
        }

        result += generateShift(level) + "};\n";

        return result;
    }

private:
    string m_name;
    using Fields = vector< shared_ptr< Unit > >;
    vector< Fields > m_fields;
};

const vector< string > cs_ClassUnit::ACCESS_MODIFIERS = { "public", "protected", "private" };

class cs_MethodUnit : public Unit
{
public:
    enum Modifier
    {
        STATIC = 1,
        //CONST = 1 << 1,
        VIRTUAL = 1 << 2,
        DEFAULT = 1 << 3
    };
public:

    cs_MethodUnit(const string& name,
        const string& returnType,
        Flags flags, int arg_num = 0, ...) :
        m_name(name),
        m_returnType(returnType),
        m_flags(flags)
    {
        if (arg_num > 0)
        {
            va_list argptr;
            __crt_va_start(argptr, arg_num);

            for (; arg_num; --arg_num)
            {
                m_args.push_back(__crt_va_arg(argptr, const char*));
            }
            __crt_va_end(argptr);
        }
    }

    void add(const shared_ptr< Unit >& unit, Flags /* flags */ = 0)
    {
        m_body.push_back(unit);
    }

    string compile(unsigned int level = 0) const
    {
        string result = generateShift(level);

        if (m_flags & STATIC)
        {
            result += "static ";
        }
        //else if (m_flags & VIRTUAL)
        //{
        //    result += "virtual ";
        //}

        result += m_returnType + " ";
        result += m_name + "(";

        {
            size_t size = m_args.size();
            for (size_t i = 0; i < size; ++i)
            {
                result += m_args[i];
                if (i < size - 1)
                    result += ", ";
            }
        }

        result += ")";

        //if (m_flags & CONST)
        //{
        //    result += " const";
        //}

        result += " {\n";

        for (const auto& b : m_body)
        {
            result += b->compile(level + 2);
        }

        result += generateShift(level + 1) + "}\n";

        return result;
    }

private:

    string m_name;
    string m_returnType;
    Flags m_flags;
    vector< shared_ptr< Unit > > m_body;
    vector< string > m_args;
};

class cs_PrintOperatorUnit : public Unit
{
public:
    explicit cs_PrintOperatorUnit(const string& text) :
        m_text(text)
    {}
    string compile(unsigned int level = 0) const
    {
        return generateShift(level) + "Console.WriteLine( \"" + m_text +
            "\" );\n";
    }
private:
    string m_text;
};

class CsCodeGenerator : CodeGenerator
{

public:
    explicit CsCodeGenerator() {}

    Unit* getClassCode(string class_name = "MyClass") const override final
    {
        cs_ClassUnit* Class = new cs_ClassUnit(class_name);

        Class->add(
            make_shared< cs_MethodUnit >("testFunc1", "void", 0),
            cs_ClassUnit::PUBLIC
        );

        Class->add(
            make_shared< cs_MethodUnit >("testFunc2", "void",
                cs_MethodUnit::STATIC),
            cs_ClassUnit::PRIVATE
        );

        Class->add(
            make_shared< cs_MethodUnit >("testFunc3", "void",
                cs_MethodUnit::VIRTUAL, 3, "int", "double", "UserType"),
            cs_ClassUnit::PUBLIC
        );

        auto method = make_shared< cs_MethodUnit >("testFunc4",
            "void", cs_MethodUnit::STATIC);

        method->add(make_shared< cs_PrintOperatorUnit >("Hello, world!"));
        Class->add(method, cs_ClassUnit::PROTECTED);

        return Class;
    }

};

int main()
{
    //alarm ! утечки (похуй)
    cout << CppCodeGenerator().getClassCode()->compile() << endl;
    cout << JavaCodeGenerator().getClassCode()->compile() << endl;
    cout << CsCodeGenerator().getClassCode()->compile() << endl;

    system("pause");
    return 0;
}
