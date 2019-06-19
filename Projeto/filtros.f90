PROGRAM FILTRO

IMPLICIT NONE

 integer*8, parameter:: N=1024
 real*8, parameter  :: PI=3.14159
 real*8,allocatable  :: reX(:), imX(:), t(:), magX(:)
 integer*8   :: i, j, kernel

 allocate(reX(0:N-1), imX(0:N-1), t(0:N-1), magX(0:N-1))

 open(110,file="Papaco.csv")
 open(120,file="Impulso_Tempo.dat")
 open(130,file="Janelamento_500.dat")
 open(140,file="Filtrado_500.dat")

 kernel=500 !Tamanho do Kernel

 reX=0.0

 !Recolhendo os dados do sinal
 do i=0, (N/2)-1
    read(110,*) imX(i), reX(i)
 end do

 imX=0.0

 imX= -imX !Invertendo o imX

 !Aplicando a FFT
 CALL FFT(reX, imX, N, PI)

 !Dividindo o domínio por N, e invertendo o imX
 reX=reX/float(N)
 imX=-imX/float(N)

 !Passando os dados da resposta ao Impulso no domínio do tempo
 do i=0, N-1
  write(120,*) i, sqrt(reX(i)*reX(i)+imX(i)*imX(i))
 end do

 !Aplicando o Janelamento
 CALL JANELAMENTO(reX, imX, N, PI, kernel)

 do i=0, (N/2)-1
  write(130,*) i, sqrt(reX(i)*reX(i)+imX(i)*imX(i))
 end do

 !Aplicando novamente a FFT
 CALL FFT(reX, imX, N, PI)

 !Para retornar ao valor original, é necessário multiplicar a magnitude por um fator de 2
 do i=0, (N/2)-1
  magX(i)= 2*sqrt(reX(i)*reX(i) + imX(i)*imX(i))
  t(i)=float(i)/float(N)
 end do

 do i=0, (N/2)-1
  write(140,*) t(i), magX(i)
 end do 

END PROGRAM

!-------------------- Rotina FFT --------------------

SUBROUTINE FFT(reX, imX, N, PI)

    integer*8 :: N, i, j, k , m, ip, l, le, le2
    real*8   :: reX(0:N-1), imX(0:N-1)
    real*8   :: PI, tr, ti, sr, si, ur,ui

    m=int(log(float(N))/log(float(2)))

    j=(N/2)
    do i=1, N-2
        if (i < j) then
            tr=reX(j)
                ti=imX(j)
                reX(j)=reX(i)
                imX(j)=imX(i)
                reX(i) =tr
                imX(i)=ti        
        end if      

        k=(N/2)
    
        do while (k <= j) 
            j = j-k
            k = k/2
        enddo 
        j = j+k
    end do 

    do l=1, m 
        le =int(2**l)
        le2=int(int(le)/int(2))
        ur=1.0
        ui=0.0
        sr=cos(PI/float(le2))
        si=(-1)*sin(PI/float(le2))
        
        do j=1, le2 
            do i=(j-1), (N-1), le
                ip=i+le2
                tr=(reX(ip)*ur) - (imX(ip)*ui)
                ti=(reX(ip)*ui) + (imX(ip)*ur)
                reX(ip)=reX(i) - tr
                imX(ip)=imX(i) - ti
                reX(i)=reX(i) + tr
                imX(i)=imX(i) + ti
            end do  
            tr=ur
            ur=(tr*sr) - (ui*si)
            ui=(tr*si) + (ui*sr)
        end do 
    end do
    return

END SUBROUTINE

!------------------------------------------------------------


!-------------------- Rotina JANELAMENTO --------------------

SUBROUTINE JANELAMENTO(reX, imX, N, PI, kernel)

 integer*8 :: N, i, j, k , kernel, ip, ind
    real*8   :: reX(0:N-1), imX(0:N-1), t(0:N-1)
    real*8   :: PI
    
    do i=0, N-1
  ind = i + int(kernel/2)    !deslocando para o centro 
  if (ind > N-1) then
   ind=ind-N
  end if
  t(ind)=reX(i)
  reX(i)=0.0
  imX(i)=0.0
 end do 

 reX=t

 do i=0, N-1
  if (i <= kernel) then
   reX(i) = reX(i) * (0.54 - 0.46*cos((2.*PI*i)/kernel))    ! window
  else  
   reX(i) = 0.0
   imX(i) = 0.0
  end if
 end do

END SUBROUTINE
