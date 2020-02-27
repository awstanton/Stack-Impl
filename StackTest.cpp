#include "StackTest.h"
#include "Stack.h"
#include <string>

class StackFixture {
public:
    Stack<std::string> ss1;
    Stack<std::string> ss2;
    Stack<int> is1;
    Stack<int> is2;

    StackFixture() : ss1(Stack<std::string>(0)), ss2(Stack<std::string>(10)), is1(Stack<int>(0)), is2(Stack<int>(10)) {
        ss1.push(std::string("hello11"));
        ss1.push(std::string("hello12"));
        ss1.push(std::string("hello13"));
        ss2.push(std::string("hello21"));
        ss2.push(std::string("hello22"));
        ss2.push(std::string("hello23"));
        is1.push(11);
        is1.push(12);
        is1.push(13);
        is2.push(21);
        is2.push(22);
        is2.push(23);
    }
};

SUITE(Ctor) {
    TEST(zeroCapacity) {
        Stack<std::string> ss = Stack<std::string>(0);
        CHECK_EQUAL(ss.getSize(), 0);
        CHECK_EQUAL(ss.getCapacity(), 0);

        Stack<int> is = Stack<int>(0);
        CHECK_EQUAL(is.getSize(), 0);
        CHECK_EQUAL(is.getCapacity(), 0);
    }

    TEST(positiveCapacity) {
        Stack<std::string> ss = Stack<std::string>(10);
        CHECK_EQUAL(ss.getSize(), 0);
        CHECK_EQUAL(ss.getCapacity(), 10);

        Stack<int> is = Stack<int>(10);
        CHECK_EQUAL(is.getSize(), 0);
        CHECK_EQUAL(is.getCapacity(), 10);
    }
}

SUITE(Push) {
    TEST_FIXTURE(StackFixture, PushTest) {
        CHECK_EQUAL(ss1.getCapacity(), (unsigned int) 4);
        CHECK_EQUAL(ss1.getSize(), (unsigned int) 3);
        CHECK_EQUAL(ss2.getCapacity(), (unsigned int) 10);
        CHECK_EQUAL(ss2.getSize(), (unsigned int) 3);
        CHECK_EQUAL(is1.getCapacity(), (unsigned int) 4);
        CHECK_EQUAL(is1.getSize(), (unsigned int) 3);
        CHECK_EQUAL(is2.getCapacity(), (unsigned int) 10);
        CHECK_EQUAL(is2.getSize(), (unsigned int) 3);
    }
}

SUITE(Pop) {
    TEST_FIXTURE(StackFixture, PopTest) {
        ss1.pop();
        CHECK_EQUAL(ss1.getCapacity(), 4);
        CHECK_EQUAL(ss1.getSize(), 2);
        ss1.pop();
        CHECK_EQUAL(ss1.getCapacity(), 4);
        CHECK_EQUAL(ss1.getSize(), 1);
        ss1.pop();
        CHECK_EQUAL(ss1.getCapacity(), 4);
        CHECK_EQUAL(ss1.getSize(), 0);
        CHECK_THROW(ss1.pop(), std::underflow_error);
        ss2.pop();
        CHECK_EQUAL(ss2.getCapacity(), 10);
        CHECK_EQUAL(ss2.getSize(), 2);
        ss2.pop();
        CHECK_EQUAL(ss2.getCapacity(), 10);
        CHECK_EQUAL(ss2.getSize(), 1);
        ss2.pop();
        CHECK_EQUAL(ss2.getCapacity(), 10);
        CHECK_EQUAL(ss2.getSize(), 0);
        is1.pop();
        CHECK_EQUAL(is1.getCapacity(), 4);
        CHECK_EQUAL(is1.getSize(), 2);
        is1.pop();
        CHECK_EQUAL(is1.getCapacity(), 4);
        CHECK_EQUAL(is1.getSize(), 1);
        is1.pop();
        CHECK_EQUAL(is1.getCapacity(), 4);
        CHECK_EQUAL(is1.getSize(), 0);
        CHECK_THROW(is1.pop(), std::underflow_error);
        is2.pop();
        CHECK_EQUAL(is2.getCapacity(), 10);
        CHECK_EQUAL(is2.getSize(), 2);
        is2.pop();
        CHECK_EQUAL(is2.getCapacity(), 10);
        CHECK_EQUAL(is2.getSize(), 1);
        is2.pop();
        CHECK_EQUAL(is2.getCapacity(), 10);
        CHECK_EQUAL(is2.getSize(), 0);
    }
}

SUITE(Peek) {
    TEST(PeekString) {
        Stack<std::string> ss = Stack<std::string>(0);
        CHECK_THROW(ss.peek(), std::out_of_range);
        ss.push("name");
        CHECK_EQUAL(ss.peek(), "name");
        ss.push("word");
        CHECK_EQUAL(ss.peek(), "word");
        ss.pop();
        CHECK_EQUAL(ss.peek(), "name");
        ss.pop();
        CHECK_THROW(ss.peek(), std::out_of_range);
    }
    TEST(PeekInt) {
        Stack<int> is = Stack<int>(20);
        CHECK_THROW(is.peek(), std::out_of_range);
        is.push(10000);
        CHECK_EQUAL(is.peek(), 10000);
        is.push(20000);
        CHECK_EQUAL(is.peek(), 20000);
        is.pop();
        CHECK_EQUAL(is.peek(), 10000);
        is.pop();
        CHECK_THROW(is.peek(), std::out_of_range);
    }
}

/*
peek
    - before push or pop
    - after push
    - after pop
    - after copy
    - after assignment
    - after destruction
*/

SUITE(CopyCtor) {
    TEST(empty) {
        Stack<int> is(1000);
        Stack<int> nis(is);
        CHECK_EQUAL(nis.getSize(), is.getSize());
        CHECK_EQUAL(nis.getSize(), 0);
        CHECK_EQUAL(nis.getCapacity(), is.getCapacity());
        CHECK_EQUAL(nis.getCapacity(), 1000);

        Stack<std::string> ss(500);
        Stack<std::string> nss(ss);
        CHECK_EQUAL(nss.getSize(), ss.getSize());
        CHECK_EQUAL(nss.getSize(), 0);
        CHECK_EQUAL(nss.getCapacity(), ss.getCapacity());
        CHECK_EQUAL(nss.getCapacity(), 500);
    }
    TEST(nonEmpty) {
        Stack<int> is(10000);
        is.push(-10);
        is.push(-20);
        is.push(-30);
        is.push(-40);
        is.push(-50);
        Stack<int> nis(is);
        CHECK_EQUAL(nis.getSize(), is.getSize());
        CHECK_EQUAL(nis.getSize(), 5);
        CHECK_EQUAL(nis.getCapacity(), is.getCapacity());
        CHECK_EQUAL(nis.getCapacity(), 10000);
        CHECK_EQUAL(nis.peek(), -50);
        CHECK_EQUAL(nis.pop(), -50);
        CHECK_EQUAL(nis.peek(), -40);
        CHECK_EQUAL(nis.pop(), -40);
        CHECK_EQUAL(nis.peek(), -30);
        CHECK_EQUAL(nis.pop(), -30);
        CHECK_EQUAL(nis.peek(), -20);
        CHECK_EQUAL(nis.pop(), -20);
        CHECK_EQUAL(nis.peek(), -10);
        CHECK_EQUAL(nis.pop(), -10);
        CHECK_THROW(nis.pop(), std::underflow_error);
        CHECK_THROW(nis.peek(), std::out_of_range);
        CHECK_EQUAL(is.peek(), -50);
        CHECK_EQUAL(is.pop(), -50);
        nis.push(999);
        CHECK_EQUAL(nis.peek(), 999);

        Stack<std::string> ss(5000);
        ss.push("a");
        ss.push("b");
        ss.push("c");
        ss.push("d");
        ss.push("e");
        Stack<std::string> nss(ss);
        CHECK_EQUAL(nss.getSize(), ss.getSize());
        CHECK_EQUAL(nss.getSize(), 5);
        CHECK_EQUAL(nss.getCapacity(), ss.getCapacity());
        CHECK_EQUAL(nss.getCapacity(), 5000);
        nss.push("na");
        CHECK_EQUAL(nss.peek(), "na");
        CHECK_EQUAL(nss.pop(), "na");
        CHECK_EQUAL(ss.peek(), "e");
        CHECK_EQUAL(ss.pop(), "e");
    }
}

/*
copy constructor
    - empty stack
    - stack with single element
    - stack with multiple elements
*/

SUITE(Assignment) {
    TEST(Empty) {
        Stack<int> is1(1000);
        Stack<int> is2(is1);
        Stack<int> is3(50);
        is3 = is2;
        CHECK_EQUAL(is3.getCapacity(), is2.getCapacity());
        CHECK_EQUAL(is3.getSize(), is2.getSize());
        is1 = is1;
        CHECK_EQUAL(is1.getCapacity(), is2.getCapacity());
        CHECK_EQUAL(is2.getCapacity(), is3.getCapacity());
        CHECK_EQUAL(is1.getSize(), is2.getSize());
        CHECK_EQUAL(is2.getSize(), is3.getSize());

        Stack<int> ss1(1000);
        Stack<int> ss2(ss1);
        Stack<int> ss3(50);
        ss3 = ss2;
        CHECK_EQUAL(ss3.getCapacity(), ss2.getCapacity());
        CHECK_EQUAL(ss3.getSize(), ss2.getSize());
        ss1 = ss1;
        CHECK_EQUAL(ss1.getCapacity(), ss2.getCapacity());
        CHECK_EQUAL(ss2.getCapacity(), ss3.getCapacity());
        CHECK_EQUAL(ss1.getSize(), ss2.getSize());
        CHECK_EQUAL(ss2.getSize(), ss3.getSize());
    }
    TEST(NonEmpty) {
        Stack<int> is1(1000);
        is1.push(999);
        is1.push(-999);

        Stack<int> is2(10);
        is2 = is1;

        is1.push(99);
        is1.push(-99);

        CHECK_EQUAL(is1.getSize(), 4);
        CHECK_EQUAL(is2.getSize(), 2);
        CHECK_EQUAL(is1.getCapacity(), 1000);
        CHECK_EQUAL(is2.getCapacity(), 1000);
        CHECK_EQUAL(is1.peek(), -99);
        CHECK_EQUAL(is2.peek(), -999);
        CHECK_EQUAL(is1.pop(), -99);
        CHECK_EQUAL(is1.pop(), 99);
        CHECK_EQUAL(is1.pop(), -999);
        CHECK_EQUAL(is1.pop(), 999);
        CHECK_EQUAL(is2.pop(), -999);
        CHECK_EQUAL(is2.pop(), 999);
        CHECK_EQUAL(is1.getSize(), 0);
        CHECK_EQUAL(is2.getSize(), 0);

        Stack<std::string> ss1(500);
        ss1.push("a1");
        ss1.push("b2");

        Stack<std::string> ss2(10);
        ss2 = ss1;

        ss1.push("c3");
        ss1.push("d4");

        CHECK_EQUAL(ss1.getSize(), 4);
        CHECK_EQUAL(ss2.getSize(), 2);
        CHECK_EQUAL(ss1.getCapacity(), 500);
        CHECK_EQUAL(ss2.getCapacity(), 500);
        CHECK_EQUAL(ss1.peek(), "d4");
        CHECK_EQUAL(ss2.peek(), "b2");
        CHECK_EQUAL(ss1.pop(), "d4");
        CHECK_EQUAL(ss1.pop(), "c3");
        CHECK_EQUAL(ss1.pop(), "b2");
        CHECK_EQUAL(ss1.pop(), "a1");
        CHECK_EQUAL(ss2.pop(), "b2");
        CHECK_EQUAL(ss2.pop(), "a1");
        CHECK_EQUAL(is1.getSize(), 0);
        CHECK_EQUAL(is2.getSize(), 0);
    }

    TEST(ZeroCapacity) {
        Stack<int> is1(0);
        Stack<int> is2(is1);
        Stack<int> is3(100);

        is3.push(1);
        is3.push(2);
        is3.push(3);

        is3 = is2;

        CHECK_EQUAL(is1.getCapacity(), 0);
        CHECK_EQUAL(is2.getCapacity(), 0);
        CHECK_EQUAL(is3.getCapacity(), 0);
        CHECK_EQUAL(is1.getSize(), 0);
        CHECK_EQUAL(is2.getSize(), 0);
        CHECK_EQUAL(is3.getSize(), 0);

        Stack<std::string> ss1(100);
        Stack<std::string> ss2(ss1);
        Stack<std::string> ss3(0);

        ss1.push("aaa");
        ss1.push("bbb");
        ss1.push("ccc");

        ss3 = ss1;

        CHECK_EQUAL(ss1.getCapacity(), 100);
        CHECK_EQUAL(ss2.getCapacity(), 100);
        CHECK_EQUAL(ss3.getCapacity(), 100);
        CHECK_EQUAL(ss1.getSize(), 3);
        CHECK_EQUAL(ss2.getSize(), 0);
        CHECK_EQUAL(ss3.getSize(), 3);

        CHECK_EQUAL(ss1.pop(), "ccc");
        CHECK_EQUAL(ss1.pop(), "bbb");
        CHECK_EQUAL(ss1.pop(), "aaa");

        CHECK_EQUAL(ss3.pop(), "ccc");
        CHECK_EQUAL(ss3.pop(), "bbb");
        CHECK_EQUAL(ss3.pop(), "aaa");

        CHECK_EQUAL(ss1.getCapacity(), 100);
        CHECK_EQUAL(ss2.getCapacity(), 100);
        CHECK_EQUAL(ss3.getCapacity(), 100);
        CHECK_EQUAL(ss1.getSize(), 0);
        CHECK_EQUAL(ss2.getSize(), 0);
        CHECK_EQUAL(ss3.getSize(), 0);
    }
}

SUITE(Dtor) {
    TEST (Destructor) {
        Stack<int> is(100);
        Stack<std::string> ss(100);

//        is.Stack<int>::~Stack();
//
//        ss.Stack<std::string>::~Stack();
    }


/*
destructor
    - empty
    - one element
    - multiple elements
*/
}


/*
pop
    - before push
    - after push
    - after peek
    - multiple times
    - after copy
    - after assignment
    - after destruction
*/
/*
push
    - push multiple elements
    - push after peek
    - push after pop
    - after copy
    - after assignment
    - after destruction
*/
/*
assignment operator
    - self-reference
    - empty assigned to multiple element
    - multiple element assigned to empty
    - multiple element assigned to multiple element
    - empty assigned to empty
*/
