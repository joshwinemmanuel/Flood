<ComClass(ComClass1.ClassId, ComClass1.InterfaceId, ComClass1.EventsId)> _
Public Class ComClass1

#Region "COM GUIDs"
    ' These  GUIDs provide the COM identity for this class 
    ' and its COM interfaces. If you change them, existing 
    ' clients will no longer be able to access the class.
    Public Const ClassId As String = "4eec152e-a935-4b3f-9fab-a69e4664f587"
    Public Const InterfaceId As String = "456e9e17-dcef-4cba-8e0e-00f7ee385f23"
    Public Const EventsId As String = "00728c66-5e7b-4f20-a289-f053fef90088"
#End Region

    ' A creatable COM class must have a Public Sub New() 
    ' with no parameters, otherwise, the class will not be 
    ' registered in the COM registry and cannot be created 
    ' via CreateObject.
    Public Sub New()
        MyBase.New()
    End Sub

End Class


