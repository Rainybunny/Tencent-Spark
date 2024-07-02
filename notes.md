$$
\textit{Litar!}
\newcommand{\opn}[1]{\operatorname{#1}}
\newcommand{\card}[0]{\opn{card}}
\newcommand{\E}[0]{\exist}
\newcommand{\A}[0]{\forall}
\newcommand{\l}[0]{\left}
\newcommand{\r}[0]{\right}
\newcommand{\eps}[0]{\varepsilon}
\newcommand{\Ra}[0]{\Rightarrow}
\newcommand{\Eq}[0]{\Leftrightarrow}
\newcommand{\d}[0]{\text{d}}
\newcommand{\der}[1]{\frac{\d}{\d #1}}
\newcommand{\oo}[0]{\infty}
\newcommand{\T}[0]{\intercal}
\newcommand{\pmat}[1]{\begin{pmatrix}#1\end{pmatrix}}
$$

## 1.1 Hilbert 空间

&emsp;&emsp;Hilbert 空间 (在有限维下是一个 $\C^n$) $\mathcal H$ 中的一向量 $\ket{\psi}$ 描述了一量子系统的物理性质, 称 $\mathcal H$ 为量子态空间, $\ket{\psi}$ 为态向量. 在 $(\C^n\setminus\{\ket 0\},\parallel)$, 同一等价类中的向量描述的物理性质相同. $\ket u,\ket v\in\mathcal H\Ra\ket u+\ket v\in\mathcal H$, 这是所谓 "量子叠加"?

&emsp;&emsp;对 $\mathcal H=\C^n$, 可以选取一组基向量 $\{\ket{\phi_{0..{n-1}}}\}$, 显然 $\A\ket\psi\in\mathcal H,~\E\{c_{0..{n-1}}\}\in\C^n,~\sum_{i=0}^{n-1}c_i\ket{\phi_i}=\psi$, 这时, 记
$$
\ket\psi\cong\pmat{c_0 & c_1 & \cdots & c_{n-1}}^\intercal
$$
为 $\ket\psi$ 在 $\{\ket{\phi_{0..n-1}}\}$ 下的表示. 这里展开系数 $c_i$ 称为几率幅.

&emsp;&emsp;$\ket v$ 的共轭转置 (对偶) 向量记为 $\bra v\cong\pmat{v_0^* & v_1^* & \cdots & v_{n-1}^*}$, 两向量 $\ket v$ 和 $\ket w$ 的内积可记为
$$
\braket{v|w}=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}v_i^*w_j\braket{\phi_i|\phi_j},
$$
其满足 $\braket{v|w}=\braket{w|v}^*$, $\braket{v|v}\ge 0$, 后者可以给出常见意义下向量长度 (即 $2$-范数):
$$
\|v\|_2=\sqrt{\sum_{i=0}^{n-1}|v_i|^2}=\sqrt{\braket{v|v}}.
$$
称长度为 $1$ 的向量为单位向量. 此后, 默认描述系统的量子态的长度为 $1$ (相当于用单位球壳描述了 $(\C^n\setminus\{0\},\parallel)$).

&emsp;&emsp;如果两个向量 $\ket v$ 和 $\ket w$ 满足 $\braket{v|w}=0$, 就称二者是正交的. 选定一组基 $\{\ket i\mid i=0,1,\dots,n-1\}$ (这种记法真的混乱邪恶), 满足
$$
\braket{j|i}=[i=j],
$$
(那你为什么还要再 "且 $\|i\|_2=1$?") 那么这组基称为正交归一. 未经说明, 以下均采用正交归一基. 此时,
$$
\braket{v|w}=\sum_{i}v_i^*w_i,\\
\ket v\bra w=\pmat{
	v_0w_0^* & \cdots & v_0w_{n-1}^*\\
	\vdots & \ddots & \vdots\\
	v_{n-1}w_0^* & \cdots & v_{n-1}w_{n-1}^*
}.
$$

## 1.2 Schrödinger 方程

&emsp;&emsp;自动忽视所有我不需要和没办法关心的事实. (

&emsp;&emsp;Schrödinger 方程给出
$$
i\frac{\d\ket{\psi(t)}}{\d t}=H(t)\ket{\psi(t)},
$$
其中 $t$ 是时间, $H(t)$ 是一个厄米算子, 称为系统的哈密顿量. 这样, 从初始时间 $t_i$ 到终止时间 $t_f$ 的演化可以等效地写为
$$
\ket{\psi_{t_f}}=U(t_f,t_i)\ket{\psi_{t_i}},
$$
其中 $U(t_f,t_i)$ 是一个幺正算符.

## 1.3 量子态测量

&emsp;&emsp;量子测量由一族测量算子 $\{M_k\}_{k=1}^l$ 构成, 其满足 $\sum_{k=1}^k M_k^\dagger M_k=I$. 量子态 $\ket\psi\in\mathcal H$ 在测量后立即以 $p_k$ 的概率变成
$$
\ket\psi\mapsto\frac{M_k\ket\psi}{\sqrt{p_k}}=:\ket{\psi_k}.
$$
其中 $p_k=\|M_k\ket\psi\|_2^2$.