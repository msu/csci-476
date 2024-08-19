void foo(int x) {
    int a; 
    a = x;
}

void bar() {
    int b = 5;
    foo(b);
}

int main() {
    bar();
    return 0;
}
