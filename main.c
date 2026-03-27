#include "zhouyi_algebra.h"
#include <stdio.h>
#include <stdlib.h>

big_gua calc_pow2(int p) {
    big_gua res = big_gua_from_string("1");
    big_gua two = big_gua_from_string("2");

    for (int i = 0; i < p; i++) {
        big_gua temp = big_gua_mul(res, two);
        big_gua_free(&res);
        res = temp;
    }
    big_gua_free(&two);
    return res;
}

int lucas_lehmer_test(int p, big_gua mp) {
    if (p == 2) return 1;

    big_gua s = big_gua_from_string("4");
    big_gua neg_two = big_gua_negate(big_gua_from_string("2"));

    for (int i = 0; i < p - 2; i++) {
        big_gua s_sq = big_gua_mul(s, s);
        big_gua s_sq_minus_2 = big_gua_add(s_sq, neg_two);
        big_gua next_s = big_gua_mod(s_sq_minus_2, mp);

        big_gua_free(&s);
        big_gua_free(&s_sq);
        big_gua_free(&s_sq_minus_2);
        s = next_s;

        if ((i + 1) % 5 == 0) {
            printf(".");
        }
    }
    printf("\n");
    int is_prime = big_gua_is_zero(s);
    big_gua_free(&s);
    big_gua_free(&neg_two);

    return is_prime;
}

int main() {
    printf("================================================\n");
    printf("      Zhouyi Algebra - 推演大衍之数\n");
    printf("================================================\n\n");

    int primes_to_test[] = {2, 3, 5, 7, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    int num_tests = sizeof(primes_to_test) / sizeof(primes_to_test[0]);

    big_gua neg_one = big_gua_negate(big_gua_from_string("1"));

    for (int i = 0; i < num_tests; i++) {
        int p = primes_to_test[i];
        printf("欲测 p = %d\n", p);

        big_gua pow2 = calc_pow2(p);
        big_gua mp = big_gua_add(pow2, neg_one);
        big_gua_free(&pow2);

        char* mp_str = big_gua_to_string(mp);
        printf("得数 M_%d = %s\n", p, mp_str);
        printf("卦象: ");
        print_big_gua_tight(mp);
        printf("\n");
        free(mp_str);

        if (lucas_lehmer_test(p, mp)) {
            printf("曰梅森素数\n\n");
        } else {
            printf("曰合数\n\n");
        }

        big_gua_free(&mp);
    }

    big_gua_free(&neg_one);
    printf("练得身形似鹤形，千株松下两函经；我来问道无余说，云在青天水在瓶。\n");
    return 0;
}
