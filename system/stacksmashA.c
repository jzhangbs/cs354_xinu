void rec(int n) {
    if (n == 1) return;
    rec(n-1);
}

void stacksmashA() {
    rec(100);
}
