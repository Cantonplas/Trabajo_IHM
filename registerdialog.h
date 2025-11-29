#include <QDialog>
#include "navtypes.h" // Asegúrate de incluir esto

namespace Ui { class RegisterDialog; }

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor normal (para registrar nuevo)
    explicit RegisterDialog(QWidget *parent = nullptr);

    // Constructor para EDITAR (recibe el usuario a editar)
    explicit RegisterDialog(User* userToEdit, QWidget *parent = nullptr);

    ~RegisterDialog();

private slots:
    void on_btnSave_clicked(); // Asumimos que tu botón guardar se llama así

private:
    Ui::RegisterDialog *ui;
    User *m_userToEdit = nullptr; // Puntero para saber si editamos o creamos
    bool m_editMode = false;      // Bandera para saber el modo
};
