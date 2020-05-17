# Tex2MathML

This is a converter, converting special HTML files containing latex math environments.
The program accepts these special HTML files and functions like a filter,
translating the contained tex expressions into MathML code.

The program translates HTML code containing LaTex math environments like the following:

SNIP

<h3>Entropie</h3>
<p>
        In <a href = "https://de.wikipedia.org/wiki/Stirlingformel" target = _top>Stirling'scher Näherung</a> für große $N$
        $$
                N!\approx N^N\cdot e^{-N}
        $$
        lautet die kombinatorische Variable $C$:
        $$
                C=\frac{N!}{\prod_i n_i!}\approx \frac{N^N\cdot e^{-N}}{\prod_i n_i^{n_i}\cdot e^{-n_i}}=\frac{N^N}{\prod_i n_i^{n_i}}.
        $$
        Der Logarithmus der kombinatorischen Variable $C$ lautet:
        \begin{eqnarray}
                \log(C) & \approx & N\cdot \log(N)-\sum\limits_i n_i\cdot \log(n_i)\\
                        & \approx & N\cdot \log(N)-N\cdot \sum\limits_i p_i\cdot \log(N\cdot p_i)\\
                        & \approx & N\cdot \log(N)-N\cdot \log(N)\cdot \sum\limits_i p_i-N\cdot \sum\limits_i p_i\cdot \log(p_i)\\
                        & \approx & -N \cdot \sum\limits_i p_i\cdot \log(p_i)
        \end{eqnarray}
</p><p>
        Man erkennt hier, dass der teilchenspezifische Logarithmus
        der kombinatorischen Variablen proportional ist zur <a href = "https://de.wikipedia.org/wiki/Entropie" target = _top>Entropie</a>:
        $$
                S(p_i)=k_B\cdot \frac{\log(C)}{N}=-k_B\cdot \sum\limits_i p_i\cdot\log(p_i),
        $$
        wobei $k_B$ die <a href = "https://de.wikipedia.org/wiki/Boltzmann-Konstante" target = _top>Boltzmann-Konstante</a> ist.
</p>

END SNIP

into

SNIP

<h3>Entropie</h3>
<p>
        In <a href = "https://de.wikipedia.org/wiki/Stirlingformel" target = _top>Stirling'scher Näherung</a> für große <math><mi>N</mi></math>
        <math class="equation" mode="display">
                <mi>N</mi><mo>!</mo><mo>&#x2248;</mo> <msup><mi>N</mi><mi>N</mi></msup><mo>&#x22c5;</mo> <msup><mi>e</mi><mrow><mo>-</mo><mi>N</mi></mrow></msup>
        </math>
        lautet die kombinatorische Variable <math><mi>C</mi></math>:
        <math class="equation" mode="display">
                <mi>C</mi><mo>=</mo><mfrac><mrow><mi>N</mi><mo>!</mo></mrow><mrow><msub><mo>&#x220f;</mo><mi>i</mi></msub> <msub><mi>n</mi><mi>i</mi></msub><mo>!</mo></mrow></mfrac><mo>&#x2248;</mo> <mfrac><mrow><msup><mi>N</mi><mi>N</mi></msup><mo>&#x22c5;</mo> <msup><mi>e</mi><mrow><mo>-</mo><mi>N</mi></mrow></msup></mrow><mrow><msub><mo>&#x220f;</mo><mi>i</mi></msub> <msubsup><mi>n</mi><mi>i</mi><mrow><msub><mi>n</mi><mi>i</mi></msub></mrow></msubsup><mo>&#x22c5;</mo> <msup><mi>e</mi><mrow><mo>-</mo><msub><mi>n</mi><mi>i</mi></msub></mrow></msup></mrow></mfrac><mo>=</mo><mfrac><mrow><msup><mi>N</mi><mi>N</mi></msup></mrow><mrow><msub><mo>&#x220f;</mo><mi>i</mi></msub> <msubsup><mi>n</mi><mi>i</mi><mrow><msub><mi>n</mi><mi>i</mi></msub></mrow></msubsup></mrow></mfrac><mo>.</mo>
        </math>
        Der Logarithmus der kombinatorischen Variable <math><mi>C</mi></math> lautet:
        <math class="equation" mode="display"><mtable displaystyle="true" columnalign="right center left"><mtr><mtd>
                <mo>log</mo><mfenced><mi>C</mi></mfenced> </mtd><mtd> <mo>&#x2248;</mo> </mtd><mtd> <mi>N</mi><mo>&#x22c5;</mo> <mo>log</mo><mfenced><mi>N</mi></mfenced><mo>-</mo><munder><mo>&#x2211;</mo><mi>i</mi></munder> <msub><mi>n</mi><mi>i</mi></msub><mo>&#x22c5;</mo> <mo>log</mo><mfenced><mrow><msub><mi>n</mi><mi>i</mi></msub></mrow></mfenced></mtd></mtr><mtr><mtd>
                        </mtd><mtd> <mo>&#x2248;</mo> </mtd><mtd> <mi>N</mi><mo>&#x22c5;</mo> <mo>log</mo><mfenced><mi>N</mi></mfenced><mo>-</mo><mi>N</mi><mo>&#x22c5;</mo> <munder><mo>&#x2211;</mo><mi>i</mi></munder> <msub><mi>p</mi><mi>i</mi></msub><mo>&#x22c5;</mo> <mo>log</mo><mfenced><mrow><mi>N</mi><mo>&#x22c5;</mo> <msub><mi>p</mi><mi>i</mi></msub></mrow></mfenced></mtd></mtr><mtr><mtd>
                        </mtd><mtd> <mo>&#x2248;</mo> </mtd><mtd> <mi>N</mi><mo>&#x22c5;</mo> <mo>log</mo><mfenced><mi>N</mi></mfenced><mo>-</mo><mi>N</mi><mo>&#x22c5;</mo> <mo>log</mo><mfenced><mi>N</mi></mfenced><mo>&#x22c5;</mo> <munder><mo>&#x2211;</mo><mi>i</mi></munder> <msub><mi>p</mi><mi>i</mi></msub><mo>-</mo><mi>N</mi><mo>&#x22c5;</mo> <munder><mo>&#x2211;</mo><mi>i</mi></munder> <msub><mi>p</mi><mi>i</mi></msub><mo>&#x22c5;</mo> <mo>log</mo><mfenced><mrow><msub><mi>p</mi><mi>i</mi></msub></mrow></mfenced></mtd></mtr><mtr><mtd>
                        </mtd><mtd> <mo>&#x2248;</mo> </mtd><mtd> <mo>-</mo><mi>N</mi> <mo>&#x22c5;</mo> <munder><mo>&#x2211;</mo><mi>i</mi></munder> <msub><mi>p</mi><mi>i</mi></msub><mo>&#x22c5;</mo> <mo>log</mo><mfenced><mrow><msub><mi>p</mi><mi>i</mi></msub></mrow></mfenced>
        </mtd></mtr></mtable></math>
</p><p>
        Man erkennt hier, dass der teilchenspezifische Logarithmus
        der kombinatorischen Variablen proportional ist zur <a href = "https://de.wikipedia.org/wiki/Entropie" target = _top>Entropie</a>:
        <math class="equation" mode="display">
                <mi>S</mi><mfenced><mrow><msub><mi>p</mi><mi>i</mi></msub></mrow></mfenced><mo>=</mo><msub><mi>k</mi><mi>B</mi></msub><mo>&#x22c5;</mo> <mfrac><mrow><mo>log</mo><mfenced><mi>C</mi></mfenced></mrow><mi>N</mi></mfrac><mo>=</mo><mo>-</mo><msub><mi>k</mi><mi>B</mi></msub><mo>&#x22c5;</mo> <munder><mo>&#x2211;</mo><mi>i</mi></munder> <msub><mi>p</mi><mi>i</mi></msub><mo>&#x22c5;</mo><mo>log</mo><mfenced><mrow><msub><mi>p</mi><mi>i</mi></msub></mrow></mfenced><mo>,</mo>
        </math>
        wobei <math><msub><mi>k</mi><mi>B</mi></msub></math> die <a href = "https://de.wikipedia.org/wiki/Boltzmann-Konstante" target = _top>Boltzmann-Konstante</a> ist.
</p>

END SNIP

The file tex_symbols.txt contains a list of 1:1 latex: MathML translations. The file format is found in 'tex2mml_data_types.h'
looking at the definition of the struct TexSymbol_s data type.

Compile it with a simple make on a linux system with g++ installed.
On other systems and using other compilers please modify 'makefile' to make it fit your needs.

If you want to assess the performance of the translator, have a look at http://www.tim-deutschmann.de. All formulas on the page are created using the Tex2MathML converter.

Cheers
