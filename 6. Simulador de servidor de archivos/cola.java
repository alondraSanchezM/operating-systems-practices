//Alondra Sánchez Molina         201732614

public class Cola {
    private int [] valores;    
    private int max, frente, fondo, numElementos;

    public Cola(int max) {
        this.max = max;
        valores= new int[this.max];
    }


    public Cola() {
        max=5;
        frente=0;
        fondo=0;
        numElementos=0;
        valores= new int[max];
    }
    
    public boolean estaVacia(){
        if(fondo==frente && numElementos==0)
           return true;
        else
           return false;
    }

    public boolean estaLlena(){
        if(fondo==frente && numElementos!=0)
           return true;
        else
           return false;
    }

    public int getNumElementos() {
        return numElementos;
    }
    
    public void encolar(int dato){      
        valores[fondo]=dato;
        fondo=(fondo+1)%max;
        numElementos++;
    }
    
    public int desencolar(){
        int valor;
        valor=valores[frente];
        frente=(frente+1)%max;
        numElementos--;
        return valor;
    }
    
    public int peek(){
        return valores[frente];
    }

    public void mostrar(){
        if(frente<fondo)
        for(int i=frente; i<fondo; i=(i+1)%max)
            System.out.println(" - "+valores[i]);
        else{
            for(int i=frente; i<max; i++)
                System.out.println(" - "+valores[i]);
            for(int i=0; i<fondo; i++)
                System.out.println(" - "+valores[i]);
        }   
    }
}
