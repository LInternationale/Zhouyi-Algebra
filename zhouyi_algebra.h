// Zhou Yi Algebra

#ifndef JIAJINGOS_ZHOUYI_ALGEBRA_H
#define JIAJINGOS_ZHOUYI_ALGEBRA_H

typedef struct {
    unsigned char bit0 : 1; // 下卦初爻
    unsigned char bit1 : 1; // 下卦二爻
    unsigned char bit2 : 1; // 下卦三爻
    unsigned char bit3 : 1; // 上卦初爻
    unsigned char bit4 : 1; // 上卦二爻
    unsigned char bit5 : 1; // 上卦三爻
    unsigned char overflow : 1;
    unsigned char yinyang : 1;
} gua;

typedef struct {
    gua* guas;
    int len;
} big_gua;

unsigned char get_val(gua g);
gua make_gua(unsigned char val);
const char* get_trigram_name(unsigned char val);
const char* get_xiang_zhuan(unsigned char val);
void num_to_zh(unsigned char val, char* buf);
void print_yao(unsigned char bit);
void print_gua(gua g);
const char* get_unicode_gua(unsigned char val);
void print_gua_tight(gua g);
gua cuo(gua a);
gua gua_and(gua a, gua b);
gua gua_or(gua a, gua b);
gua gua_xor(gua a, gua b);
gua gua_add(gua a, gua b);
big_gua big_gua_from_string(const char* str);
void big_gua_free(big_gua* bg);
char* big_gua_to_string(big_gua bg);
big_gua big_gua_add(big_gua a, big_gua b);
void print_big_gua_tight(big_gua bg);
big_gua big_gua_zero(void);
big_gua big_gua_negate(big_gua a);
int big_gua_is_zero(big_gua a);
big_gua big_gua_abs(big_gua a);
big_gua big_gua_trim(big_gua a);
big_gua big_gua_mul(big_gua a, big_gua b);
int big_gua_unsigned_cmp(big_gua a, big_gua b);
big_gua big_gua_copy(big_gua a);
big_gua big_gua_div(big_gua a, big_gua b);
big_gua big_gua_mod(big_gua a, big_gua b);

#endif //JIAJINGOS_ZHOUYI_ALGEBRA_H