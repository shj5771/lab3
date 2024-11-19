use std::io;

fn main() {
    // 첫 번째 행렬의 크기를 입력받습니다.
    println!("첫 번째 행렬의 크기를 입력하세요 (행, 열): ");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("입력 실패");
    let dims: Vec<usize> = input
        .trim()
        .split_whitespace()
        .map(|s| s.parse().expect("숫자가 아닙니다"))
        .collect();
    let (rows, cols) = (dims[0], dims[1]);

    // 두 번째 행렬의 크기를 입력받습니다.
    println!("두 번째 행렬의 크기를 입력하세요 (행, 열): ");
    input.clear();
    io::stdin().read_line(&mut input).expect("입력 실패");
    let dims2: Vec<usize> = input
        .trim()
        .split_whitespace()
        .map(|s| s.parse().expect("숫자가 아닙니다"))
        .collect();
    let (rows2, cols2) = (dims2[0], dims2[1]);

    // 두 행렬의 크기가 일치하는지 확인합니다.
    if rows != rows2 || cols != cols2 {
        println!("두 행렬의 크기가 일치하지 않습니다!");
        return;
    }

    // 첫 번째 행렬의 값을 입력받습니다.
    let mut matrix1: Vec<Vec<i32>> = Vec::with_capacity(rows);
    println!("첫 번째 행렬의 값을 입력하세요:");
    for i in 0..rows {
        let mut row: Vec<i32> = Vec::with_capacity(cols);
        for j in 0..cols {
            print!("행 {} 열 {} 값: ", i + 1, j + 1);
            input.clear();
            io::stdin().read_line(&mut input).expect("입력 실패");
            let value: i32 = input.trim().parse().expect("숫자가 아닙니다");
            row.push(value);
        }
        matrix1.push(row);
    }

    // 두 번째 행렬의 값을 입력받습니다.
    let mut matrix2: Vec<Vec<i32>> = Vec::with_capacity(rows2);
    println!("두 번째 행렬의 값을 입력하세요:");
    for i in 0..rows2 {
        let mut row: Vec<i32> = Vec::with_capacity(cols2);
        for j in 0..cols2 {
            print!("행 {} 열 {} 값: ", i + 1, j + 1);
            input.clear();
            io::stdin().read_line(&mut input).expect("입력 실패");
            let value: i32 = input.trim().parse().expect("숫자가 아닙니다");
            row.push(value);
        }
        matrix2.push(row);
    }

    // 두 행렬을 더한 결과를 저장할 새로운 행렬을 생성합니다.
    let mut result_matrix: Vec<Vec<i32>> = Vec::with_capacity(rows);
    for i in 0..rows {
        let mut result_row: Vec<i32> = Vec::with_capacity(cols);
        for j in 0..cols {
            result_row.push(matrix1[i][j] + matrix2[i][j]);
        }
        result_matrix.push(result_row);
    }

    // 두 행렬의 합을 출력합니다.
    println!("두 행렬의 합:");
    for i in 0..rows {
        for j in 0..cols {
            print!("{} ", result_matrix[i][j]);
        }
        println!();
    }
}
