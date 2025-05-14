section .data 
   const2 dq 2.0
   const2minus dq -2.0 
   const1minus dq -1.0 
   const1 dq 1.0
   const3 dq 3.0
 section .text
 global f1
 ; f1 = e^x + 2
 ;удобное представление e^x = 2^(x*log e)
 f1:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fldl2e
    fmulp
    fld1
    fscale ; возводит 2 в степень int            
    fxch ; меняем последние два числа на стеке
    fld1
    fxch                
    fprem    ; получили остаток от деления первого числа на второе           
    f2xm1               
    faddp st1,st0       
    fmulp st1,st0
    fld qword[const2]
    faddp
    pop ebp
    ret
;f2 = -1/x
global f2
f2:
    push ebp
    mov ebp, esp
    finit
    fld qword[const1minus]
    fld qword[ebp + 8]
    fdivp
    pop ebp
    ret
global f3
;f3 = −2 (x + 1) / 3 
f3:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fld1 
    faddp 
    fld qword[const2minus]
    fmulp
    fld qword[const3]
    fdivp
    pop ebp
    ret
 ;производная от функции e^x + 2 = e^x
 global df1
 df1:
    ; код аналогичен вычислению e^x + 2 без добавления 2
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fldl2e
    fmulp
    fld1
    fscale             
    fxch
    fld1
    fxch                
    fprem               
    f2xm1               
    faddp st1,st0       
    fmulp st1,st0
    pop ebp
    ret
;производная от функции -1/x = +1/x^2
 global df2
df2:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fld qword[ebp + 8] 
    fmulp ;вычислили x^2
    fld qword[const1]
    fdivrp
    pop ebp
    ret
global df3
;;производная от функции  −2 (x + 1) / 3  = -2/3
df3:
    push ebp
    mov ebp, esp
    finit
    fld qword[const2minus]
    fld qword[const3]
    fdivp
    pop ebp
    ret
