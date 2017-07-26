import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;


public class Departamento implements Serializable{

	private String nome;
	private Object codigoDepartamento;//nao pode existir mais de 1 dept. com a mesma sigla
	//permitir criacao de novos depts.
	// TEM VARIOS CURSOS para 1 departamento	
	
	static Object [][] array = { {"","",""} };

	ArrayList<Object> dadosDepts = new ArrayList<Object>(Arrays.asList(array));

	
	public Object getCodigoDepartamento() {
		return codigoDepartamento;
	}
	public void setCodigoDepartamento(Object object) {
		this.codigoDepartamento = object;
	}
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public boolean validaCodigoDept(){
		boolean resultado = false;
		
		return resultado;		
	}

	//método construtor
	public Departamento(String nome,String codigo){
		this.setNome(nome);
		this.setCodigoDepartamento(codigo);
	}
	public Departamento() {
	
	}
}