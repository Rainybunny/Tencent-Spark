### Task 2-2

&emsp;&emsp;对于泡利矩阵 $P$, 欲证
$$
\exp(i\theta P)=\cos(\theta)I+i\sin(\theta)P.
$$
注意到 $PP^\dagger=PP=I$ ("即是泡利的又是厄米的"), 根据 $\exp$ 定义展开:
$$
\begin{aligned}
	\exp(i\theta P) &= \sum_{k=0}^\oo\frac{(i\theta P)^k}{k!}\\
	&= \sum_{k=0}^\oo\frac{(i\theta)^{2k}}{(2k)!}I+\sum_{k=0}^\oo\frac{(i\theta)^{2k+1}}{(2k+1)!}P,
\end{aligned}
$$
(良定性就不证了, 直接拆开求和.) 根据三角函数的级数定义,
$$
\cos\theta:=\frac{e^{i\theta}+e^{-i\theta}}{2},\quad\sin\theta:=\frac{e^{i\theta}-e^{-i\theta}}{2i},
$$
不难看出 $\exp(i\theta P)=\cos(\theta)I+i\sin(\theta)P$. 事实上, 任何满足 $P^2=I$ 的矩阵都满足这一要求.

### Task 2-3

&emsp;&emsp;规律有点奇怪...? $\hat P$ 取行上矩阵, $\hat Q$ 取列上矩阵时, $y=f(\hat P,\hat Q;\theta)$ 有:
$$
\begin{array}{c|ccc}
y&X&Y&Z\\ \hline
X&0&\sin\theta&\cos\theta\\
Y&-\sin\theta&0&\cos\theta\\
Z&0&0&1
\end{array}
$$

### Task 2-4

&emsp;&emsp;$X_iZ_j$ 形式的张量积记号表示该张量积的结果等价于令 $i$-qubit 过 $X$, $j$-qubit 过 $Z$ 而其他 qubit(s) 不改变.

### Task 2-5

&emsp;&emsp;例如, $v^\dagger\hat Q v=\bra{v}\hat Q\ket v$.
$$
\begin{aligned}
	\frac{1}{\sqrt 2}(\ket{010}-\ket{101}) &= \frac{1}{\sqrt 2}\left(\begin{pmatrix}0&0&1&0&0&0&0&0\end{pmatrix}^\intercal-\begin{pmatrix}0&0&0&0&0&1&0&0\end{pmatrix}^\intercal\right)\\
	&= \begin{pmatrix}0&0&1/\sqrt 2&0&0&-1/\sqrt 2&0&0\end{pmatrix}^\intercal.
\end{aligned}
$$
