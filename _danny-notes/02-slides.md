---
layout: slide
theme: white
transition: slide
---

<section data-markdown>

## Lecture 2: Mathematical Preliminaries

$\nabla\cdot\mathbf{E} = \frac{\rho}{\epsilon_0} \qquad \int \mathbf{E}\cdot d\mathbf{A} = \int \frac{\rho}{\epsilon_0} d\tau$

$\nabla\cdot\mathbf{B} = 0 \qquad \int \mathbf{B} \cdot d\mathbf{A} = 0$

$\nabla\times\mathbf{E} = - \frac{\partial\mathbf{B}}{\partial t} \qquad \int \mathbf{E} \cdot d\mathbf{l} = - \int \frac{\partial\mathbf{B}}{\partial t} \cdot d\mathbf{A}$


$\nabla\times\mathbf{B} = \mu_0\mathbf{J} + \mu_0\epsilon_0\frac{\partial\mathbf{E}}{\partial t} \qquad \int \mathbf{B} \cdot d\mathbf{A} = \mu_0 \int \left(\mathbf{J} + \epsilon_0 \frac{\partial\mathbf{E}}{\partial t}\right) \cdot d\mathbf{A} $


</section>

<section data-markdown>

<img src ="./images/charges_in_plane.png" align="right" style="width: 350px";/>

Two charges +Q and -Q are fixed a distance r apart.  The direction of the force on a test charge -q at  A is...

1. Up
2. Down
3. Left
4. Right
5. Some other direction, or $F = 0$


Note:
* CORRECT ANSWER:  A
* Student Responses: [[92]] 4 0 2 2 (Sp 2013)
* SJP Comment: The first concept test, it went quickly, and when they did it silently it was about 70% correct. I used this to point out that even elementary questions are easy to mess up, and conversing with neighbors “fixes” simple problems. We can’t move in if 1/3 of the class is getting THIS wrong! Mentioned to some individuals that E is down, which was a nice reminder for them.


</section>

<section data-markdown>

In a typical Cartesian coordinate system, vector $\mathbf{A}$ lies along the $+\hat{x}$ direction and vector $\mathbf{B}$ lies along the $-\hat{y}$ direction. What is the direction of $\mathbf{A} \times \mathbf{B}$?

1. $-\hat{x}$
2. $+\hat{y}$
3. $+\hat{z}$
4. $-\hat{z}$
5. Can't tell

Note:
* Correct Answer: D

</section>

<section data-markdown>

In a typical Cartesian coordinate system, vector $\mathbf{A}$ lies along the $+\hat{x}$ direction and vector $\mathbf{B}$ lies along the $-\hat{y}$ direction. What is the direction of $\mathbf{B} \times \mathbf{A}$?

1. $-\hat{x}$
2. $+\hat{y}$
3. $+\hat{z}$
4. $-\hat{z}$
5. Can't tell

Note:
* Correct Answer: C

</section>

<section data-markdown>

<img src ="./images/cq_spherical.png" align="right" style="width: 350px";/>

### You derive it

Consider the radial unit vector ($\hat{r}$) in the spherical coordinate system as shown in the figure to the right. Determine the components of this unit vector in the Cartesian $(x,y,z)$ system.

</section>
<section data-markdown>

<img src ="./images/cq_vector_in_cylindrical.png" align="right" style="width: 350px";/>


In cylindrical (2D) coordinates, what would be the correct description of the position vector $\mathbf{r}$ of the point P shown at $(x,y) = (1, 1)$?

1. $\mathbf{r} = \sqrt{2} \hat{s}$
2. $\mathbf{r} = \sqrt{2} \hat{s} + \pi/4 \hat{\phi}$
3. $\mathbf{r} = \sqrt{2} \hat{s} - \pi/4 \hat{\phi}$
4. $\mathbf{r} = \pi/4 \hat{\phi}$
5. Something else entirely

Note:
* CORRECT ANSWER:  A
* INSTRUCTOR NOTES This was the “review’ question to start class. We had done almost exactly the same question at the start of the previous class, so I thought it would be even higher. (The position vector is different from the coordinates! Students seem to be confused about this - the point P has r=Sqrt[2], phi=pi/4, but it is certainly not the case that, e.g.  B would be the position vector. The units aren’t even correct!)   -SJP

</section>

<section data-markdown>

How is the vector $\mathfrak{R}_{12}$ related to $\mathbf{r}_1$ and  $\mathbf{r}_2$?

<img src ="./images/cq_r1r2.png" align="right" style="width: 350px";/>

1. $\mathfrak{R}_{12} = \mathbf{r}_1 +\mathbf{r}_2$
1. $\mathfrak{R}_{12} = \mathbf{r}_1 - \mathbf{r}_2$
1. $\mathfrak{R}_{12} = \mathbf{r}_2 - \mathbf{r}_1$
4. None of these

Note:
* CORRECT ANSWER:  C
* SJP Comment: Nice concept test. I asked my students first: given a charge q1 and r1 and q2 at r2, what physical vector does Coulomb’s law implicitly have in it,i..e  what’s the “r vector” in the simple version of Coulomb’s law? I got several responses, including the sum (average) of r1 and r2, or the difference…  That lead beautifully into this question. Silently they were about 70% correct, after brief discussion it went to 90+%. It’s not hard, but very worth while. The point here is that R12 as shown is clearly what you physically want, and then the picture tells you how to construct it, this is not something to “memorize”, it just makes sense!

</section>

<section data-markdown>

Coulomb's Law: $\mathbf{F}  = \frac{k q_1 q_2}{\left|\mathfrak{R}\right|^2}\hat{\mathfrak{R}}$ where $\mathfrak{R}$ is the relative position vector. In the figure, $q_1$ and $q_2$ are 2 m apart. Which arrow **can** represent $\hat{\mathfrak{R}}$?

<img src ="./images/cq_unit_r.png" align="center" style="width: 550px";/>

1. A
2. B
3. C
4. More than one (or NONE) of the above
5. You can't decide until you know if $q_1$ and $q_2$ are the same or opposite charges


</section>


<section data-markdown>

You are trying to compute the work done by a force, $\mathbf{F} = a\hat{x} + x\hat{y}$, along the line $y=2x$ from $\langle 0,0 \rangle$ to $\langle 1,2 \rangle$. What is $d\mathbf{l}$?

1. $dl$
2. $dx\;\hat{x}$
3. $dy\;\hat{y}$
4. $2dx\;\hat{x}$
5. Something else

Note:
Correct answer: E (It's $dx\;\hat{x}+dy\;\hat{y}$).

</section>

<section data-markdown>

You are trying to compute the work done by a force, $\mathbf{F} = a\hat{x} + x\hat{y}$, along the line $y=2x$ from $\langle 0,0 \rangle$ to $\langle 1,2 \rangle$. Given that $d\mathbf{l} = dx\;\hat{x}+dy\;\hat{y}$, which of the following forms of the integral is correct?

1. $\int_0^1 a\;dx + \int_0^2 x\;dy)$
2. $\int_0^1 (a\;dx + 2x\;dx)$
3. $\frac{1}{2} \int_0^2 (a\;dy + y\;dy)$
4. More than one is correct

Note:
Correct answer: D (All are correct forms, but B and C are ready to integrate).

</section>


<section data-markdown>

A certain fluid has a velocity field given by $\mathbf{v} = x\hat{x} + z \hat{y}$. Which component of the field contributed to "fluid flux" integral ($\int_S \mathbf{v}\cdot d\mathbf{A}$) through the x-z plane?

1. $v_x$
2. $v_y$
3. both
4. neither

Note:
* Correct answer: B
* Only the vector perpendicular to the surface will contribute

</section>

<section data-markdown>

For the same fluid with velocity field given by $\mathbf{v} = x\hat{x} + z \hat{y}$. What is the value of the "fluid flux" integral ($\int_S \mathbf{v}\cdot d\mathbf{A}$) through the entire x-y plane?

1. It is zero
2. It is something finite
3. It is infinite
4. I can't tell without doing the integral

Note:
* Correct answer: A
* The velocity field is parallel to the x-y plane every where and hence contributes no flux through the surface.

</section>

<section data-markdown>

A rod (radius $R$) with a hole (radius $r$) drilled down its entire length $L$ has a mass density of $\frac{m_0\phi}{\phi_0}$ (where $\phi$ is the normal polar coordinate).

To find the total mass of this rod, which coordinate system should be used (take note that the mass density varies as a function of angle):

1. Cartesian ($x,y,z$)
2. Spherical ($r,\phi,\theta$)
3. Cylindrical ($s, \phi, z$)
4. It doesn't matter, just pick one.

</section>

<section data-markdown>

Which of the following two fields has zero divergence?

<img src ="./images/cq_two_fields.png" align="center" style="width: 700px";/>

1. Both do.
2. Only I is zero
3. Only II is zero
4. Neither is zero
5. ???

</section>

<section data-markdown>

Which of the following two fields has zero curl?

<img src ="./images/cq_two_fields.png" align="center" style="width: 700px";/>

1. Both do.
2. Only I is zero
3. Only II is zero
4. Neither is zero
5. ???

</section>

<section data-markdown>
Consider a vector field defined as the gradient of some well-behaved scalar function:
$$\mathbf{v}(x,y,z) = \nabla T(x,y,z).$$

What is the value of $\oint_C \mathbf{v} \cdot d\mathbf{l}$?

1. Zero
2. Non-zero, but finite
3. Can't tell without a function for $T$

</section>
