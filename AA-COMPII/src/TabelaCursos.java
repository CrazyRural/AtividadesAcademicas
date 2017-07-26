import java.util.ArrayList;

import javax.swing.JTable;


public class TabelaCursos extends JTable{
	
	private static ArrayList<Curso> rows;
	
	public void preenche(){
		for (int i = 0; i < rows.size(); i++) {
			this.setValueAt(rows.get(i).getNome(), i, 0);
			this.setValueAt(rows.get(i).getCodigoCurso(), i, 1);
			this.setValueAt(AdicionarCurso.comboBox.getSelectedItem(), i, 2);			
		}
	}

	public void preencheVazio(){
		for (int i = 0; i < rows.size()+1; i++) {
			this.setValueAt("", i, 0);
			this.setValueAt("", i, 1);
			this.setValueAt("", i, 2);
		}
	}
	
	
	@Override
	public boolean isCellEditable(int row,int col){
		return false;
	}

	public TabelaCursos(ArrayList<Curso> rows, String[] columns){
		super(rows.size()+30,columns.length);
		this.rows = rows;
		
		for (int i = 0; i < columns.length; i++) {
			this.getColumnModel().getColumn(i).setHeaderValue(columns[i]);	
		}
		
		this.preenche();
	}
}