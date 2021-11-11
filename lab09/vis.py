from turtle import Turtle, Screen
from sys import argv

# typing
from typing import List, Tuple

X_TELA = 400
Y_TELA = 300


def ler(filename: str) -> List[tuple]:
    ret = []
    with open(filename, 'r') as f:
        for line in f:
            coords = line.strip().split()
            ret.append((float(coords[0]), float(coords[1])))
    return ret


def exibir(lista: List[tuple]) -> None:
    def calcula_coords(x: float, y: float) -> Tuple[float, float]:
        return (x, Y_TELA/2 - y)

    t = Turtle()
    t.hideturtle()
    s = Screen()
    s.setup(X_TELA * 2, Y_TELA * 2)
    t.up()
    t.goto(*calcula_coords(0, 0))
    t.write("0, 0", True, "center")
    t.goto(*calcula_coords(200, 0))
    t.down()

    for x, y in lista:
        x, y = calcula_coords(x, y)
        t.goto(x, y)

    input("Digite qualquer tecla pra fechar")


if __name__ == "__main__":
    if len(argv) != 2:
        print("Argumentos invalidos")
        print("Uso: python %s arquivo.txt" % argv[0])
        print("\nO arquivo deve conter uma coordenada por linha, e a coordenada x, y deve estar separada por um espaço")
        print("Exemplo de arquivo.txt: \n123.4 567.89\n9876.5 4321.0\n...")
        exit(1)

    arquivo = argv[1]
    lis = ler(arquivo)
    exibir(lis)
