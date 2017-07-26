import java.util.ArrayList;

import javax.swing.JTable;


public class TabelaAlunos extends JTable{
	
	private ArrayList<Aluno> alunoRows;
	
	
	public ArrayList<Aluno> getAlunoRows() {
		return alunoRows;
	}


	public void setAlunoRows(ArrayList<Aluno> alunoRows) {
		this.alunoRows = alunoRows;
	}


	public void preencheVazio(){
		for (int i = 0; i < alunoRows.size()+1; i++) {
			this.setValueAt("", i, 0);
			this.setValueAt("", i, 1);
			this.setValueAt("", i, 2);
			this.setValueAt("",i,3);
			
		}
	}
	
	
	public void preenche(){

		for (int i = 0; i < alunoRows.size(); i++) {
			this.setValueAt(alunoRows.get(i).getNome(), i, 0);
			this.setValueAt(alunoRows.get(i).getMatricula(), i, 1);
			this.setValueAt(alunoRows.get(i).getAnoIngresso(), i, 2);
			this.setValueAt(AdicionarAluno.comboBox.getSelectedItem(),i,3);
			this.setValueAt(alunoRows.get(i).getTicketsComprados(),i,4);
		}
	}
	
	@Override
	public boolean isCellEditable(int row,int col){
		return false;
	}

	public TabelaAlunos(ArrayList<Aluno> rows, String[] columns){
		super(rows.size()+30,columns.length);
		this.alunoRows = rows;
		
		for (int i = 0; i < columns.length; i++) {
			this.getColumnModel().getColumn(i).setHeaderValue(columns[i]);	
		}
		
		this.preenche();
	}

}
