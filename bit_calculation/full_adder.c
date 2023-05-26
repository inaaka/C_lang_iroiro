// 全加算器プログラム

#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 16 /* 文字列の最大サイズ(最大桁数) */

// 文字列用構造体
typedef struct STRING
{
    char *str;
    unsigned mem_size;
    unsigned len;
} String;

// 2進数の入力
String input_binary_number()
{
    String data;

    // メモリの確保
    data.str = (char *)malloc(MAX_STRING_SIZE);
    if (data.str == NULL) /* メモリ確保失敗時 */
    {
        data.mem_size = 0;
        fprintf(stderr, "Failed to allocate memory");
    }
    else /* メモリ確保成功時 */
    {
        data.mem_size = MAX_STRING_SIZE;

        // 二進数長の調査
        printf("input: ");
        fgets(data.str, MAX_STRING_SIZE, stdin);

        // 大きさの確認
        int i;
        for (i = data.len = 0; i < MAX_STRING_SIZE; i++)
        {
            if (data.str[i] == '0' || data.str[i] == '1')
            {
                data.len += 1;
            }
            else
            {
                break;
            }
        }
    }

    return data;
}

// 二進数の右詰め
void right_justify(String *data)
{
    int i, j;
    for (i = data->len - 1, j = data->mem_size - 2; i >= 0; i--, j--)
    {
        data->str[j] = data->str[i];
    }
    for (; j >= 0; j--)
    {
        data->str[j] = '0';
    }
}

// 全加算器
String full_adder(String a, String b)
{
    String result;

    result.str = (char *)malloc(MAX_STRING_SIZE);
    if (result.str == NULL) /* メモリ確保失敗時 */
    {
        result.mem_size = 0;
        fprintf(stderr, "Failed to allocate memory");

        return result;
    }
    else /* メモリ確保成功時 */
    {
        result.str[MAX_STRING_SIZE - 1] = '\0';
        result.mem_size = MAX_STRING_SIZE;
        result.len = (a.len > b.len) * (a.len - b.len) + b.len;

        int i, c;
        for (i = MAX_STRING_SIZE - 2, c = 0; i >= 0; i--)
        {
            int i_a = a.str[i] - '0';
            int i_b = b.str[i] - '0';
            result.str[i] = '0' + (i_a ^ i_b) ^ c;
            if ((i_a & i_b) || (i_b & c) || (c & i_a))
            {
                c = 1;
            }
            else
            {
                c = 0;
            }
        }

        return result;
    }
}

// 2進数 -> 10進数
int binary_to_10(String binary)
{
    int result;

    int i, n;
    for (i = binary.mem_size - 2, n = 1, result = 0; i >= binary.mem_size - binary.len - 1; i--, n *= 2)
    {
        result += (binary.str[i] - '0') * n;
    }

    return result;
}

// full_adder関数の動作テスト
int main(void)
{
    // 入力1
    String input1 = input_binary_number();
    if (input1.mem_size == 0)
    {
        return EXIT_FAILURE;
    }
    if (input1.len == 0)
    {
        fprintf(stderr, "binary input not found");
        return EXIT_FAILURE;
    }

    // 入力2
    String input2 = input_binary_number();
    if (input2.mem_size == 0)
    {
        free(input1.str);
        return EXIT_FAILURE;
    }
    if (input2.len == 0)
    {
        fprintf(stderr, "binary input not found");
        free(input1.str);
        return EXIT_FAILURE;
    }

    // 2進数の右詰め
    right_justify(&input1);
    right_justify(&input2);

    // 入力の計算式を出力
    printf("---\n");
    printf("equ : %d + %d = ?\n", binary_to_10(input1), binary_to_10(input2));

    // 全加算器で足し算
    String result = full_adder(input1, input2);
    free(input1.str);
    free(input2.str);
    if (result.mem_size == 0)
    {
        return EXIT_FAILURE;
    }

    // 結果を出力
    printf(">>> %s\n", result.str);
    printf(">>> %d\n", binary_to_10(result));
    free(result.str);

    return EXIT_SUCCESS;
}