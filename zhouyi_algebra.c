// Zhou Yi Algebra

#include "zhouyi_algebra.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(x) Sleep((x) * 1000)
#else
#include <unistd.h>
#define SLEEP(x) sleep(x)
#endif

unsigned char get_val(gua g) {
    return (g.bit5 << 5) | (g.bit4 << 4) | (g.bit3 << 3) |
           (g.bit2 << 2) | (g.bit1 << 1) | g.bit0;
}

gua make_gua(unsigned char val) {
    gua g;
    g.bit0 = (val >> 0) & 1;
    g.bit1 = (val >> 1) & 1;
    g.bit2 = (val >> 2) & 1;
    g.bit3 = (val >> 3) & 1;
    g.bit4 = (val >> 4) & 1;
    g.bit5 = (val >> 5) & 1;
    g.overflow = 0;
    return g;
}

const char* get_trigram_name(unsigned char val) {
    const char* names[8] = {"坤", "震", "坎", "兑", "艮", "离", "巽", "乾"};
    return names[val & 0x07];
}

const char* get_xiang_zhuan(unsigned char val) {
    const char* xiang[64] = {
        "坤卦。象曰：地势坤，君子以厚德载物。", "复卦。象曰：雷在地中，复。先王以至日闭关。", "师卦。象曰：地中有水，师。君子以容民畜众。", "临卦。象曰：泽上有地，临。君子以教思无穷。", "谦卦。象曰：地中有山，谦。君子以裒多益寡。", "明夷卦。象曰：明入地中，明夷。君子以莅众，用晦而明。", "升卦。象曰：地中生木，升。君子以顺德，积小以高大。", "泰卦。象曰：天地交，泰。后以财成天地之道。",
        "豫卦。象曰：雷出地奋，豫。先王以作乐崇德。", "震卦。象曰：洊雷，震。君子以恐惧修省。", "解卦。象曰：雷雨作，解。君子以赦过宥罪。", "归妹卦。象曰：泽上有雷，归妹。君子以永终知敝。", "小过卦。象曰：山上有雷，小过。君子以行过乎恭。", "丰卦。象曰：雷电皆至，丰。君子以折狱致刑。", "恒卦。象曰：雷风，恒。君子以立不易方。", "大壮卦。象曰：雷在天上，大壮。君子以非礼弗履。",
        "比卦。象曰：地上有水，比。先王以建万国，亲诸侯。", "屯卦。象曰：云雷，屯。君子以经纶。", "坎卦。象曰：水洊至，习坎。君子以常德行，习教事。", "节卦。象曰：泽上有水，节。君子以制数度，议德行。", "蹇卦。象曰：山上有水，蹇。君子以反身修德。", "既济卦。象曰：水在火上，既济。君子以思患而预防之。", "井卦。象曰：木上有水，井。君子以劳民劝相。", "需卦。象曰：云上于天，需。君子以饮食宴乐。",
        "萃卦。象曰：泽上于地，萃。君子以除戎器，戒不虞。", "随卦。象曰：泽中有雷，随。君子以向晦入宴息。", "困卦。象曰：泽无水，困。君子以致命遂志。", "兑卦。象曰：丽泽，兑。君子以朋友讲习。", "咸卦。象曰：山上有泽，咸。君子以虚受人。", "革卦。象曰：泽中有火，革。君子以治历明时。", "大过卦。象曰：泽灭木，大过。君子以独立不惧。", "夬卦。象曰：泽上于天，夬。君子以施禄及下。",
        "剥卦。象曰：山附于地，剥。上以厚下安宅。", "颐卦。象曰：山下有雷，颐。君子以慎言语，节饮食。", "蒙卦。象曰：山下出泉，蒙。君子以果行育德。", "损卦。象曰：山下有泽，损。君子以惩忿窒欲。", "艮卦。象曰：兼山，艮。君子以思不出其位。", "贲卦。象曰：山下有火，贲。君子以明庶政，无敢折狱。", "蛊卦。象曰：山下有风，蛊。君子以振民育德。", "大畜卦。象曰：天在山中，大畜。君子以多识前言往行。",
        "晋卦。象曰：明出地上，晋。君子以自昭明德。", "噬嗑卦。象曰：雷电噬嗑。先王以明罚敕法。", "未济卦。象曰：火在水上，未济。君子以慎辨物居方。", "睽卦。象曰：上火下泽，睽。君子以同而异。", "旅卦。象曰：山上有火，旅。君子以明慎用刑。", "离卦。象曰：明两作，离。大人以继明照于四方。", "鼎卦。象曰：木上有火，鼎。君子以正位凝命。", "大有卦。象曰：火在天上，大有。君子以遏恶扬善。",
        "观卦。象曰：风行地上，观。先王以省方观民设教。", "益卦。象曰：风雷，益。君子以见善则迁，有过则改。", "涣卦。象曰：风行水上，涣。先王以享于帝立庙。", "中孚卦。象曰：泽上有风，中孚。君子以议狱缓死。", "渐卦。象曰：山上有木，渐。君子以居贤德善俗。", "家人卦。象曰：风自火出，家人。君子以言有物而行有恒。", "巽卦。象曰：随风，巽。君子以申命行事。", "小畜卦。象曰：风行天上，小畜。君子以懿文德。",
        "否卦。象曰：天地不交，否。君子以俭德辟难。", "无妄卦。象曰：天下雷行，物与无妄。先王以茂对时育万物。", "讼卦。象曰：天与水违行，讼。君子以作事谋始。", "履卦。象曰：上天下泽，履。君子以辨上下，定民志。", "遁卦。象曰：天下有山，遁。君子以远小人，不恶而严。", "同人卦。象曰：天与火，同人。君子以类族辨物。", "姤卦。象曰：天下有风，姤。后以施命诰四方。", "乾卦。象曰：天行健，君子以自强不息。"
    };
    return xiang[val & 0x3F];
}

void num_to_zh(unsigned char val, char* buf) {
    const char* digits[] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
    if (val <= 9) {
        sprintf(buf, "%s", digits[val]);
    } else if (val == 10) {
        sprintf(buf, "十");
    } else if (val < 20) {
        sprintf(buf, "十%s", digits[val % 10]);
    } else {
        if (val % 10 == 0) {
            sprintf(buf, "%s十", digits[val / 10]);
        } else {
            sprintf(buf, "%s十%s", digits[val / 10], digits[val % 10]);
        }
    }
}

void print_yao(unsigned char bit) {
    if (bit) {
        printf("██████████\n");
    } else {
        printf("████  ████\n");
    }
}

void print_gua(gua g) {
    unsigned char upper = (g.bit5 << 2) | (g.bit4 << 1) | g.bit3;
    unsigned char lower = (g.bit2 << 2) | (g.bit1 << 1) | g.bit0;
    unsigned char val = get_val(g);

    char zh_num[32];
    num_to_zh(val, zh_num);

    print_yao(g.bit5);
    print_yao(g.bit4);
    print_yao(g.bit3);
    print_yao(g.bit2);
    print_yao(g.bit1);
    print_yao(g.bit0);

    printf("数%s 上%s下%s，%s",
           zh_num,
           get_trigram_name(upper), get_trigram_name(lower),
           get_xiang_zhuan(val));

    if (g.overflow) {
        printf("亢龙有悔，盈不可久也。");
    }
    printf("\n\n");
}

const char* get_unicode_gua(unsigned char val) {
    const char* unicode_xiang[64] = {
        "䷁", "䷗", "䷆", "䷒", "䷎", "䷣", "䷭", "䷊",
        "䷏", "䷲", "䷧", "䷵", "䷽", "䷶", "䷟", "䷡",
        "䷇", "䷂", "䷜", "䷻", "䷦", "䷾", "䷯", "䷄",
        "䷬", "䷐", "䷮", "䷹", "䷞", "䷰", "䷛", "䷪",
        "䷖", "䷚", "䷃", "䷨", "䷳", "䷕", "䷑", "䷙",
        "䷢", "䷔", "䷿", "䷥", "䷷", "䷝", "䷱", "䷍",
        "䷓", "䷩", "䷺", "䷼", "䷴", "䷤", "䷸", "䷈",
        "䷋", "䷘", "䷅", "䷉", "䷠", "䷌", "䷫", "䷀"
    };
    return unicode_xiang[val & 0x3F];
}

void print_gua_tight(gua g) {
    unsigned char upper = (g.bit5 << 2) | (g.bit4 << 1) | g.bit3;
    unsigned char lower = (g.bit2 << 2) | (g.bit1 << 1) | g.bit0;
    unsigned char val = get_val(g);

    char zh_num[32];
    num_to_zh(val, zh_num);

    printf("%s ", get_unicode_gua(val));

    printf("数%s 上%s下%s，%s",
           zh_num,
           get_trigram_name(upper), get_trigram_name(lower),
           get_xiang_zhuan(val));

    if (g.overflow) {
        printf("亢龙有悔，盈不可久也。");
    }
    printf("\n\n");
}

gua cuo(gua a) {
    gua res;
    res.bit0 = !a.bit0;
    res.bit1 = !a.bit1;
    res.bit2 = !a.bit2;
    res.bit3 = !a.bit3;
    res.bit4 = !a.bit4;
    res.bit5 = !a.bit5;
    res.overflow = 0;
    return res;
}

gua zong(gua a) {
    gua res;
    res.bit0 = a.bit5;
    res.bit1 = a.bit4;
    res.bit2 = a.bit3;
    res.bit3 = a.bit2;
    res.bit4 = a.bit1;
    res.bit5 = a.bit0;
    res.overflow = 0;
    return res;
}

gua hu(gua a) {
    gua res;
    // 下互卦
    res.bit0 = a.bit1; // 原二爻
    res.bit1 = a.bit2; // 原三爻
    res.bit2 = a.bit3; // 原四爻
    // 上互卦
    res.bit3 = a.bit2; // 原三爻
    res.bit4 = a.bit3; // 原四爻
    res.bit5 = a.bit4; // 原五爻

    res.overflow = 0;
    return res;
}

gua jiao(gua a) {
    gua res;
    res.bit0 = a.bit3;
    res.bit1 = a.bit4;
    res.bit2 = a.bit5;
    res.bit3 = a.bit0;
    res.bit4 = a.bit1;
    res.bit5 = a.bit2;

    res.overflow = 0;
    return res;
}

gua bian(gua a, int yao) {
    gua res = a;
    res.overflow = 0;

    switch(yao) {
        case 1: res.bit0 = !res.bit0; break;
        case 2: res.bit1 = !res.bit1; break;
        case 3: res.bit2 = !res.bit2; break;
        case 4: res.bit3 = !res.bit3; break;
        case 5: res.bit4 = !res.bit4; break;
        case 6: res.bit5 = !res.bit5; break;
        default: break;
    }
    return res;
}

gua gua_and(gua a, gua b) {
    gua res;
    res.bit0 = a.bit0 & b.bit0;
    res.bit1 = a.bit1 & b.bit1;
    res.bit2 = a.bit2 & b.bit2;
    res.bit3 = a.bit3 & b.bit3;
    res.bit4 = a.bit4 & b.bit4;
    res.bit5 = a.bit5 & b.bit5;
    res.overflow = 0;
    return res;
}

gua gua_or(gua a, gua b) {
    gua res;
    res.bit0 = a.bit0 | b.bit0;
    res.bit1 = a.bit1 | b.bit1;
    res.bit2 = a.bit2 | b.bit2;
    res.bit3 = a.bit3 | b.bit3;
    res.bit4 = a.bit4 | b.bit4;
    res.bit5 = a.bit5 | b.bit5;
    res.overflow = 0;
    return res;
}

gua gua_xor(gua a, gua b) {
    gua res;
    res.bit0 = a.bit0 ^ b.bit0;
    res.bit1 = a.bit1 ^ b.bit1;
    res.bit2 = a.bit2 ^ b.bit2;
    res.bit3 = a.bit3 ^ b.bit3;
    res.bit4 = a.bit4 ^ b.bit4;
    res.bit5 = a.bit5 ^ b.bit5;
    res.overflow = 0;
    return res;
}

gua gua_add(gua a, gua b) {
    gua res;
    unsigned char c = 0;

    res.bit0 = a.bit0 ^ b.bit0 ^ (c & 1);
    c |= ((a.bit0 & b.bit0) | ((c & 1) & (a.bit0 ^ b.bit0))) << 1;

    res.bit1 = a.bit1 ^ b.bit1 ^ ((c >> 1) & 1);
    c |= ((a.bit1 & b.bit1) | (((c >> 1) & 1) & (a.bit1 ^ b.bit1))) << 2;

    res.bit2 = a.bit2 ^ b.bit2 ^ ((c >> 2) & 1);
    c |= ((a.bit2 & b.bit2) | (((c >> 2) & 1) & (a.bit2 ^ b.bit2))) << 3;

    res.bit3 = a.bit3 ^ b.bit3 ^ ((c >> 3) & 1);
    c |= ((a.bit3 & b.bit3) | (((c >> 3) & 1) & (a.bit3 ^ b.bit3))) << 4;

    res.bit4 = a.bit4 ^ b.bit4 ^ ((c >> 4) & 1);
    c |= ((a.bit4 & b.bit4) | (((c >> 4) & 1) & (a.bit4 ^ b.bit4))) << 5;

    res.bit5 = a.bit5 ^ b.bit5 ^ ((c >> 5) & 1);
    c |= ((a.bit5 & b.bit5) | (((c >> 5) & 1) & (a.bit5 ^ b.bit5))) << 6;

    res.overflow = (c >> 6) & 1;

    return res;
}

big_gua big_gua_from_string(const char* str) {
    int is_negative = (str[0] == '-');
    if (is_negative) str++;

    big_gua bg;
    bg.len = 1;
    bg.guas = (gua*)calloc(1, sizeof(gua));

    while (*str) {
        int digit = *str - '0';
        if (digit < 0 || digit > 9) break;

        int carry = digit;
        for (int i = bg.len - 1; i >= 0; i--) {
            int val = get_val(bg.guas[i]) * 10 + carry;
            bg.guas[i] = make_gua(val & 0x3F);
            carry = val >> 6;
        }

        while (carry > 0) {
            bg.len++;
            bg.guas = (gua*)realloc(bg.guas, bg.len * sizeof(gua));
            memmove(&bg.guas[1], &bg.guas[0], (bg.len - 1) * sizeof(gua));
            bg.guas[0] = make_gua(carry & 0x3F);
            carry >>= 6;
        }
        str++;
    }

    if (is_negative) {
        for (int i = 0; i < bg.len; i++) {
            bg.guas[i] = make_gua((~get_val(bg.guas[i])) & 0x3F);
        }
        unsigned char carry = 1;
        for (int i = bg.len - 1; i >= 0 && carry; i--) {
            int val = get_val(bg.guas[i]) + carry;
            bg.guas[i] = make_gua(val & 0x3F);
            carry = val >> 6;
        }

        if (carry) {
            bg.len++;
            bg.guas = (gua*)realloc(bg.guas, bg.len * sizeof(gua));
            memmove(&bg.guas[1], &bg.guas[0], (bg.len - 1) * sizeof(gua));
            bg.guas[0] = make_gua(carry & 0x3F);
        }
    }

    unsigned char msb_val = get_val(bg.guas[0]);
    int msb_sign = (msb_val >> 5) & 1;
    if ((!is_negative && msb_sign == 1) || (is_negative && msb_sign == 0)) {
        bg.len++;
        bg.guas = (gua*)realloc(bg.guas, bg.len * sizeof(gua));
        memmove(&bg.guas[1], &bg.guas[0], (bg.len - 1) * sizeof(gua));
        bg.guas[0] = make_gua(is_negative ? 0x3F : 0x00);
    }

    bg.guas[0].yinyang = is_negative ? 1 : 0;
    return bg;
}

void big_gua_free(big_gua* bg) {
    if (bg->guas) {
        free(bg->guas);
        bg->guas = NULL;
    }
    bg->len = 0;
}

char* big_gua_to_string(big_gua bg) {
    if (bg.len == 0) {
        char* zero_str = (char*)malloc(2);
        strcpy(zero_str, "0");
        return zero_str;
    }

    int is_negative = bg.guas[0].yinyang;

    big_gua copy;
    copy.len = bg.len;
    copy.guas = (gua*)malloc(bg.len * sizeof(gua));

    if (is_negative) {
        unsigned char carry = 1;
        for (int i = bg.len - 1; i >= 0; i--) {
            int val = (~get_val(bg.guas[i]) & 0x3F) + carry;
            copy.guas[i] = make_gua(val & 0x3F);
            carry = val >> 6;
        }
    } else {
        for (int i = 0; i < bg.len; i++) {
            copy.guas[i] = bg.guas[i];
        }
    }

    int max_chars = bg.len * 2 + 3;
    char* temp = (char*)malloc(max_chars);
    int temp_idx = 0;

    while (1) {
        int is_zero = 1;
        for (int i = 0; i < copy.len; i++) {
            if (get_val(copy.guas[i]) != 0) { is_zero = 0; break; }
        }
        if (is_zero) break;

        int rem = 0;
        for (int i = 0; i < copy.len; i++) {
            int val = rem * 64 + get_val(copy.guas[i]);
            copy.guas[i] = make_gua(val / 10);
            rem = val % 10;
        }
        temp[temp_idx++] = rem + '0';
    }

    if (temp_idx == 0) temp[temp_idx++] = '0';

    char* result = (char*)malloc(temp_idx + 2);
    int buf_idx = 0;

    if (is_negative) result[buf_idx++] = '-';

    for (int i = temp_idx - 1; i >= 0; i--) {
        result[buf_idx++] = temp[i];
    }
    result[buf_idx] = '\0';

    free(temp);
    free(copy.guas);

    return result;
}

big_gua big_gua_add(big_gua a, big_gua b) {
    int max_len = (a.len > b.len) ? a.len : b.len;
    int res_len = max_len + 1;

    big_gua res;
    res.len = res_len;
    res.guas = (gua*)calloc(res_len, sizeof(gua));

    unsigned char carry = 0;

    for (int i = 0; i < res_len; i++) {
        int idx_a = a.len - 1 - i;
        int idx_b = b.len - 1 - i;

        unsigned char val_a = (idx_a >= 0) ? get_val(a.guas[idx_a]) : (a.guas[0].yinyang ? 0x3F : 0);
        unsigned char val_b = (idx_b >= 0) ? get_val(b.guas[idx_b]) : (b.guas[0].yinyang ? 0x3F : 0);

        gua sum1 = gua_add(make_gua(val_a), make_gua(val_b));
        gua sum2 = gua_add(sum1, make_gua(carry));

        res.guas[res_len - 1 - i] = sum2;
        carry = sum1.overflow | sum2.overflow;
    }

    unsigned char msb_val = get_val(res.guas[0]);
    res.guas[0].yinyang = (msb_val >> 5) & 1;

    return res;
}


void print_big_gua_tight(big_gua bg) {
    if (bg.len == 0) return;

    int is_negative = bg.guas[0].yinyang;

    big_gua abs_bg;
    abs_bg.len = bg.len;
    abs_bg.guas = (gua*)malloc(bg.len * sizeof(gua));

    if (is_negative) {
        unsigned char carry = 1;
        for (int i = bg.len - 1; i >= 0; i--) {
            int val = (~get_val(bg.guas[i]) & 0x3F) + carry;
            abs_bg.guas[i] = make_gua(val & 0x3F);
            carry = val >> 6;
        }
    } else {
        for (int i = 0; i < bg.len; i++) {
            abs_bg.guas[i] = bg.guas[i];
        }
    }

    printf("%s ", is_negative ? "阴" : "阳");
    for (int i = 0; i < abs_bg.len; i++) {
        printf("%s", get_unicode_gua(get_val(abs_bg.guas[i])));
    }

    free(abs_bg.guas);
}

big_gua big_gua_negate(big_gua a) {
    big_gua res;
    res.len = a.len;
    res.guas = (gua*)malloc(res.len * sizeof(gua));

    for (int i = 0; i < res.len; i++) {
        res.guas[i] = make_gua((~get_val(a.guas[i])) & 0x3F);
    }

    unsigned char carry = 1;
    for (int i = res.len - 1; i >= 0 && carry; i--) {
        int val = get_val(res.guas[i]) + carry;
        res.guas[i] = make_gua(val & 0x3F);
        carry = val >> 6;
    }

    if (carry) {
        res.len++;
        res.guas = (gua*)realloc(res.guas, res.len * sizeof(gua));
        memmove(&res.guas[1], &res.guas[0], (res.len - 1) * sizeof(gua));
        res.guas[0] = make_gua(carry & 0x3F);
    }

    unsigned char msb_val = get_val(res.guas[0]);
    res.guas[0].yinyang = (msb_val >> 5) & 1;

    return res;
}

big_gua big_gua_zero(void) {
    big_gua res;
    res.len = 1;
    res.guas = (gua*)calloc(1, sizeof(gua));
    res.guas[0].yinyang = 0;
    return res;
}

int big_gua_is_zero(big_gua a) {
    for (int i = 0; i < a.len; i++) {
        if (get_val(a.guas[i]) != 0) return 0;
    }
    return 1;
}

big_gua big_gua_abs(big_gua a) {
    if (a.guas[0].yinyang) {
        return big_gua_negate(a);
    }
    big_gua res;
    res.len = a.len;
    res.guas = (gua*)malloc(res.len * sizeof(gua));
    for (int i = 0; i < res.len; i++) {
        res.guas[i] = a.guas[i];
    }
    return res;
}

big_gua big_gua_trim(big_gua a) {
    big_gua res;
    int start = 0;

    if (a.guas[0].yinyang == 0) {
        while (start < a.len - 1 && get_val(a.guas[start]) == 0) {
            if ((get_val(a.guas[start + 1]) >> 5) & 1) break;
            start++;
        }
    } else {
        while (start < a.len - 1 && get_val(a.guas[start]) == 0x3F) {
            if (!((get_val(a.guas[start + 1]) >> 5) & 1)) break;
            start++;
        }
    }

    res.len = a.len - start;
    res.guas = (gua*)malloc(res.len * sizeof(gua));
    for (int i = 0; i < res.len; i++) {
        res.guas[i] = a.guas[start + i];
    }
    res.guas[0].yinyang = a.guas[0].yinyang;
    return res;
}

big_gua big_gua_mul(big_gua a, big_gua b) {
    int sign_a = a.guas[0].yinyang;
    int sign_b = b.guas[0].yinyang;
    int result_negative = sign_a ^ sign_b;

    big_gua abs_a = big_gua_abs(a);
    big_gua abs_b = big_gua_abs(b);

    int len_a = abs_a.len;
    int len_b = abs_b.len;
    int res_len = len_a + len_b + 1;

    unsigned int* acc = (unsigned int*)calloc(res_len, sizeof(unsigned int));

    for (int i = 0; i < len_a; i++) {
        unsigned char va = get_val(abs_a.guas[len_a - 1 - i]);
        for (int j = 0; j < len_b; j++) {
            unsigned char vb = get_val(abs_b.guas[len_b - 1 - j]);
            acc[i + j] += (unsigned int)va * vb;
        }
    }

    for (int i = 0; i < res_len - 1; i++) {
        acc[i + 1] += acc[i] >> 6;
        acc[i] &= 0x3F;
    }

    big_gua res;
    res.len = res_len;
    res.guas = (gua*)calloc(res_len, sizeof(gua));

    for (int i = 0; i < res_len; i++) {
        res.guas[res_len - 1 - i] = make_gua(acc[i] & 0x3F);
    }

    if ((get_val(res.guas[0]) >> 5) & 1) {
        res.len++;
        res.guas = (gua*)realloc(res.guas, res.len * sizeof(gua));
        memmove(&res.guas[1], &res.guas[0], (res.len - 1) * sizeof(gua));
        res.guas[0] = make_gua(0x00);
    }
    res.guas[0].yinyang = 0;

    free(acc);
    big_gua_free(&abs_a);
    big_gua_free(&abs_b);

    if (result_negative && !big_gua_is_zero(res)) {
        big_gua neg = big_gua_negate(res);
        big_gua_free(&res);
        res = neg;
    }

    big_gua trimmed = big_gua_trim(res);
    big_gua_free(&res);
    return trimmed;
}

int big_gua_unsigned_cmp(big_gua a, big_gua b) {
    int sa = 0, sb = 0;
    while (sa < a.len - 1 && get_val(a.guas[sa]) == 0) sa++;
    while (sb < b.len - 1 && get_val(b.guas[sb]) == 0) sb++;

    int eff_a = a.len - sa;
    int eff_b = b.len - sb;

    if (eff_a != eff_b) return (eff_a > eff_b) ? 1 : -1;

    for (int i = 0; i < eff_a; i++) {
        unsigned char va = get_val(a.guas[sa + i]);
        unsigned char vb = get_val(b.guas[sb + i]);
        if (va > vb) return 1;
        if (va < vb) return -1;
    }
    return 0;
}

big_gua big_gua_unsigned_sub(big_gua a, big_gua b) {
    int max_len = (a.len > b.len) ? a.len : b.len;

    big_gua res;
    res.len = max_len;
    res.guas = (gua*)calloc(res.len, sizeof(gua));

    int borrow = 0;
    for (int i = 0; i < max_len; i++) {
        int idx_a = a.len - 1 - i;
        int idx_b = b.len - 1 - i;

        int va = (idx_a >= 0) ? get_val(a.guas[idx_a]) : 0;
        int vb = (idx_b >= 0) ? get_val(b.guas[idx_b]) : 0;

        int diff = va - vb - borrow;
        if (diff < 0) {
            diff += 64;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.guas[max_len - 1 - i] = make_gua(diff & 0x3F);
    }

    if ((get_val(res.guas[0]) >> 5) & 1) {
        res.len++;
        res.guas = (gua*)realloc(res.guas, res.len * sizeof(gua));
        memmove(&res.guas[1], &res.guas[0], (res.len - 1) * sizeof(gua));
        res.guas[0] = make_gua(0x00);
    }
    res.guas[0].yinyang = 0;

    return res;
}

big_gua big_gua_shift_left_one(big_gua a) {
    big_gua res;
    res.len = a.len + 1;
    res.guas = (gua*)calloc(res.len, sizeof(gua));

    for (int i = 0; i < a.len; i++) {
        res.guas[i] = a.guas[i];
    }
    res.guas[res.len - 1] = make_gua(0);
    res.guas[0].yinyang = a.guas[0].yinyang;

    return res;
}

big_gua big_gua_copy(big_gua a) {
    big_gua res;
    res.len = a.len;
    res.guas = (gua*)malloc(res.len * sizeof(gua));
    for (int i = 0; i < res.len; i++) {
        res.guas[i] = a.guas[i];
    }
    return res;
}

void big_gua_unsigned_divmod(big_gua a, big_gua b,
                              big_gua* quotient, big_gua* remainder) {
    if (big_gua_unsigned_cmp(a, b) < 0) {
        *quotient = big_gua_zero();
        *remainder = big_gua_copy(a);
        return;
    }

    int eff_a = a.len;
    int sa = 0;
    while (sa < a.len - 1 && get_val(a.guas[sa]) == 0) sa++;
    eff_a = a.len - sa;

    int eff_b = b.len;
    int sb = 0;
    while (sb < b.len - 1 && get_val(b.guas[sb]) == 0) sb++;
    eff_b = b.len - sb;

    int q_len = eff_a - eff_b + 1;
    unsigned char* q_digits = (unsigned char*)calloc(q_len, sizeof(unsigned char));

    big_gua rem = big_gua_copy(a);

    for (int i = 0; i < q_len; i++) {
        int shift = q_len - 1 - i;

        big_gua shifted_b;
        shifted_b.len = b.len + shift;
        shifted_b.guas = (gua*)calloc(shifted_b.len, sizeof(gua));
        for (int k = 0; k < b.len; k++) {
            shifted_b.guas[k] = b.guas[k];
        }
        for (int k = b.len; k < shifted_b.len; k++) {
            shifted_b.guas[k] = make_gua(0);
        }
        shifted_b.guas[0].yinyang = 0;

        unsigned char lo = 0, hi = 63, best = 0;
        while (lo <= hi) {
            unsigned char mid = (lo + hi) / 2;

            int sb_len = shifted_b.len;
            big_gua product;
            product.len = sb_len + 1;
            product.guas = (gua*)calloc(product.len, sizeof(gua));

            unsigned int carry = 0;
            for (int k = sb_len - 1; k >= 0; k--) {
                unsigned int val = (unsigned int)get_val(shifted_b.guas[k]) * mid + carry;
                product.guas[k + 1] = make_gua(val & 0x3F);
                carry = val >> 6;
            }
            product.guas[0] = make_gua(carry & 0x3F);

            if ((get_val(product.guas[0]) >> 5) & 1) {
                product.len++;
                product.guas = (gua*)realloc(product.guas, product.len * sizeof(gua));
                memmove(&product.guas[1], &product.guas[0], (product.len - 1) * sizeof(gua));
                product.guas[0] = make_gua(0);
            }
            product.guas[0].yinyang = 0;

            int cmp = big_gua_unsigned_cmp(product, rem);
            if (cmp <= 0) {
                best = mid;
                if (mid == 63) { big_gua_free(&product); break; }
                lo = mid + 1;
            } else {
                if (mid == 0) { big_gua_free(&product); break; }
                hi = mid - 1;
            }
            big_gua_free(&product);
        }

        q_digits[i] = best;

        if (best > 0) {
            int sb_len = shifted_b.len;
            big_gua product;
            product.len = sb_len + 1;
            product.guas = (gua*)calloc(product.len, sizeof(gua));

            unsigned int carry = 0;
            for (int k = sb_len - 1; k >= 0; k--) {
                unsigned int val = (unsigned int)get_val(shifted_b.guas[k]) * best + carry;
                product.guas[k + 1] = make_gua(val & 0x3F);
                carry = val >> 6;
            }
            product.guas[0] = make_gua(carry & 0x3F);

            if ((get_val(product.guas[0]) >> 5) & 1) {
                product.len++;
                product.guas = (gua*)realloc(product.guas, product.len * sizeof(gua));
                memmove(&product.guas[1], &product.guas[0], (product.len - 1) * sizeof(gua));
                product.guas[0] = make_gua(0);
            }
            product.guas[0].yinyang = 0;

            big_gua new_rem = big_gua_unsigned_sub(rem, product);
            big_gua_free(&rem);
            big_gua_free(&product);
            rem = new_rem;
        }

        big_gua_free(&shifted_b);
    }

    int total_q_len = q_len + 1;
    quotient->len = total_q_len;
    quotient->guas = (gua*)calloc(total_q_len, sizeof(gua));
    quotient->guas[0] = make_gua(0);
    quotient->guas[0].yinyang = 0;
    for (int i = 0; i < q_len; i++) {
        quotient->guas[i + 1] = make_gua(q_digits[i]);
    }

    *remainder = rem;

    free(q_digits);

    big_gua tq = big_gua_trim(*quotient);
    big_gua_free(quotient);
    *quotient = tq;

    big_gua tr = big_gua_trim(*remainder);
    big_gua_free(remainder);
    *remainder = tr;
}

big_gua big_gua_div(big_gua a, big_gua b) {
    int sign_a = a.guas[0].yinyang;
    int sign_b = b.guas[0].yinyang;
    int result_negative = sign_a ^ sign_b;

    big_gua abs_a = big_gua_abs(a);
    big_gua abs_b = big_gua_abs(b);

    big_gua quotient, remainder;
    big_gua_unsigned_divmod(abs_a, abs_b, &quotient, &remainder);

    big_gua_free(&abs_a);
    big_gua_free(&abs_b);
    big_gua_free(&remainder);

    if (result_negative && !big_gua_is_zero(quotient)) {
        big_gua neg = big_gua_negate(quotient);
        big_gua_free(&quotient);
        return neg;
    }
    return quotient;
}

big_gua big_gua_mod(big_gua a, big_gua b) {
    int sign_a = a.guas[0].yinyang;

    big_gua abs_a = big_gua_abs(a);
    big_gua abs_b = big_gua_abs(b);

    big_gua quotient, remainder;
    big_gua_unsigned_divmod(abs_a, abs_b, &quotient, &remainder);

    big_gua_free(&abs_a);
    big_gua_free(&abs_b);
    big_gua_free(&quotient);

    if (sign_a && !big_gua_is_zero(remainder)) {
        big_gua neg = big_gua_negate(remainder);
        big_gua_free(&remainder);
        return neg;
    }
    return remainder;
}
