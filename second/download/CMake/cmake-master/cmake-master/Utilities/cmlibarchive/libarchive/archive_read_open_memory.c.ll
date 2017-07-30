; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_open_memory.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque
%struct.read_memory_data = type { i8*, i8*, i8*, i64 }

@.str = private unnamed_addr constant [10 x i8] c"No memory\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_open_memory(%struct.archive* %a, i8* %buff, i64 %size) #0 !dbg !23 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !55, metadata !56), !dbg !57
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !58, metadata !56), !dbg !59
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !60, metadata !56), !dbg !61
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !62
  %1 = load i8*, i8** %buff.addr, align 8, !dbg !63
  %2 = load i64, i64* %size.addr, align 8, !dbg !64
  %3 = load i64, i64* %size.addr, align 8, !dbg !65
  %call = call i32 @archive_read_open_memory2(%struct.archive* %0, i8* %1, i64 %2, i64 %3), !dbg !66
  ret i32 %call, !dbg !67
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_read_open_memory2(%struct.archive* %a, i8* %buff, i64 %size, i64 %read_size) #0 !dbg !35 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %read_size.addr = alloca i64, align 8
  %mine = alloca %struct.read_memory_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !68, metadata !56), !dbg !69
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !70, metadata !56), !dbg !71
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !72, metadata !56), !dbg !73
  store i64 %read_size, i64* %read_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %read_size.addr, metadata !74, metadata !56), !dbg !75
  call void @llvm.dbg.declare(metadata %struct.read_memory_data** %mine, metadata !76, metadata !56), !dbg !77
  %call = call noalias i8* @calloc(i64 1, i64 32) #4, !dbg !78
  %0 = bitcast i8* %call to %struct.read_memory_data*, !dbg !79
  store %struct.read_memory_data* %0, %struct.read_memory_data** %mine, align 8, !dbg !80
  %1 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !81
  %cmp = icmp eq %struct.read_memory_data* %1, null, !dbg !83
  br i1 %cmp, label %if.then, label %if.end, !dbg !84

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !85
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %2, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !87
  store i32 -30, i32* %retval, align 4, !dbg !88
  br label %return, !dbg !88

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %buff.addr, align 8, !dbg !89
  %4 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !90
  %p = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %4, i32 0, i32 1, !dbg !91
  store i8* %3, i8** %p, align 8, !dbg !92
  %5 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !93
  %start = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %5, i32 0, i32 0, !dbg !94
  store i8* %3, i8** %start, align 8, !dbg !95
  %6 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !96
  %start1 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %6, i32 0, i32 0, !dbg !97
  %7 = load i8*, i8** %start1, align 8, !dbg !97
  %8 = load i64, i64* %size.addr, align 8, !dbg !98
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %8, !dbg !99
  %9 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !100
  %end = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %9, i32 0, i32 2, !dbg !101
  store i8* %add.ptr, i8** %end, align 8, !dbg !102
  %10 = load i64, i64* %read_size.addr, align 8, !dbg !103
  %11 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !104
  %read_size2 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %11, i32 0, i32 3, !dbg !105
  store i64 %10, i64* %read_size2, align 8, !dbg !106
  %12 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !107
  %call3 = call i32 @archive_read_set_open_callback(%struct.archive* %12, i32 (%struct.archive*, i8*)* @memory_read_open), !dbg !108
  %13 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !109
  %call4 = call i32 @archive_read_set_read_callback(%struct.archive* %13, i64 (%struct.archive*, i8*, i8**)* @memory_read), !dbg !110
  %14 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !111
  %call5 = call i32 @archive_read_set_seek_callback(%struct.archive* %14, i64 (%struct.archive*, i8*, i64, i32)* @memory_read_seek), !dbg !112
  %15 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !113
  %call6 = call i32 @archive_read_set_skip_callback(%struct.archive* %15, i64 (%struct.archive*, i8*, i64)* @memory_read_skip), !dbg !114
  %16 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !115
  %call7 = call i32 @archive_read_set_close_callback(%struct.archive* %16, i32 (%struct.archive*, i8*)* @memory_read_close), !dbg !116
  %17 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !117
  %18 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !118
  %19 = bitcast %struct.read_memory_data* %18 to i8*, !dbg !118
  %call8 = call i32 @archive_read_set_callback_data(%struct.archive* %17, i8* %19), !dbg !119
  %20 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !120
  %call9 = call i32 @archive_read_open1(%struct.archive* %20), !dbg !121
  store i32 %call9, i32* %retval, align 4, !dbg !122
  br label %return, !dbg !122

return:                                           ; preds = %if.end, %if.then
  %21 = load i32, i32* %retval, align 4, !dbg !123
  ret i32 %21, !dbg !123
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

declare i32 @archive_read_set_open_callback(%struct.archive*, i32 (%struct.archive*, i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i32 @memory_read_open(%struct.archive* %a, i8* %client_data) #0 !dbg !38 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !124, metadata !56), !dbg !125
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !126, metadata !56), !dbg !127
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !128
  %1 = load i8*, i8** %client_data.addr, align 8, !dbg !129
  ret i32 0, !dbg !130
}

declare i32 @archive_read_set_read_callback(%struct.archive*, i64 (%struct.archive*, i8*, i8**)*) #3

; Function Attrs: nounwind uwtable
define internal i64 @memory_read(%struct.archive* %a, i8* %client_data, i8** %buff) #0 !dbg !41 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %buff.addr = alloca i8**, align 8
  %mine = alloca %struct.read_memory_data*, align 8
  %size = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !131, metadata !56), !dbg !132
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !133, metadata !56), !dbg !134
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !135, metadata !56), !dbg !136
  call void @llvm.dbg.declare(metadata %struct.read_memory_data** %mine, metadata !137, metadata !56), !dbg !138
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !139
  %1 = bitcast i8* %0 to %struct.read_memory_data*, !dbg !140
  store %struct.read_memory_data* %1, %struct.read_memory_data** %mine, align 8, !dbg !138
  call void @llvm.dbg.declare(metadata i64* %size, metadata !141, metadata !56), !dbg !142
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !143
  %3 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !144
  %p = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %3, i32 0, i32 1, !dbg !145
  %4 = load i8*, i8** %p, align 8, !dbg !145
  %5 = load i8**, i8*** %buff.addr, align 8, !dbg !146
  store i8* %4, i8** %5, align 8, !dbg !147
  %6 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !148
  %end = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %6, i32 0, i32 2, !dbg !149
  %7 = load i8*, i8** %end, align 8, !dbg !149
  %8 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !150
  %p1 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %8, i32 0, i32 1, !dbg !151
  %9 = load i8*, i8** %p1, align 8, !dbg !151
  %sub.ptr.lhs.cast = ptrtoint i8* %7 to i64, !dbg !152
  %sub.ptr.rhs.cast = ptrtoint i8* %9 to i64, !dbg !152
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !152
  store i64 %sub.ptr.sub, i64* %size, align 8, !dbg !153
  %10 = load i64, i64* %size, align 8, !dbg !154
  %11 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !156
  %read_size = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %11, i32 0, i32 3, !dbg !157
  %12 = load i64, i64* %read_size, align 8, !dbg !157
  %cmp = icmp sgt i64 %10, %12, !dbg !158
  br i1 %cmp, label %if.then, label %if.end, !dbg !159

if.then:                                          ; preds = %entry
  %13 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !160
  %read_size2 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %13, i32 0, i32 3, !dbg !161
  %14 = load i64, i64* %read_size2, align 8, !dbg !161
  store i64 %14, i64* %size, align 8, !dbg !162
  br label %if.end, !dbg !163

if.end:                                           ; preds = %if.then, %entry
  %15 = load i64, i64* %size, align 8, !dbg !164
  %16 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !165
  %p3 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %16, i32 0, i32 1, !dbg !166
  %17 = load i8*, i8** %p3, align 8, !dbg !167
  %add.ptr = getelementptr inbounds i8, i8* %17, i64 %15, !dbg !167
  store i8* %add.ptr, i8** %p3, align 8, !dbg !167
  %18 = load i64, i64* %size, align 8, !dbg !168
  ret i64 %18, !dbg !169
}

declare i32 @archive_read_set_seek_callback(%struct.archive*, i64 (%struct.archive*, i8*, i64, i32)*) #3

; Function Attrs: nounwind uwtable
define internal i64 @memory_read_seek(%struct.archive* %a, i8* %client_data, i64 %offset, i32 %whence) #0 !dbg !48 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %offset.addr = alloca i64, align 8
  %whence.addr = alloca i32, align 4
  %mine = alloca %struct.read_memory_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !170, metadata !56), !dbg !171
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !172, metadata !56), !dbg !173
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !174, metadata !56), !dbg !175
  store i32 %whence, i32* %whence.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %whence.addr, metadata !176, metadata !56), !dbg !177
  call void @llvm.dbg.declare(metadata %struct.read_memory_data** %mine, metadata !178, metadata !56), !dbg !179
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !180
  %1 = bitcast i8* %0 to %struct.read_memory_data*, !dbg !181
  store %struct.read_memory_data* %1, %struct.read_memory_data** %mine, align 8, !dbg !179
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !182
  %3 = load i32, i32* %whence.addr, align 4, !dbg !183
  switch i32 %3, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb1
    i32 2, label %sw.bb4
  ], !dbg !184

sw.bb:                                            ; preds = %entry
  %4 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !185
  %start = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %4, i32 0, i32 0, !dbg !187
  %5 = load i8*, i8** %start, align 8, !dbg !187
  %6 = load i64, i64* %offset.addr, align 8, !dbg !188
  %add.ptr = getelementptr inbounds i8, i8* %5, i64 %6, !dbg !189
  %7 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !190
  %p = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %7, i32 0, i32 1, !dbg !191
  store i8* %add.ptr, i8** %p, align 8, !dbg !192
  br label %sw.epilog, !dbg !193

sw.bb1:                                           ; preds = %entry
  %8 = load i64, i64* %offset.addr, align 8, !dbg !194
  %9 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !195
  %p2 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %9, i32 0, i32 1, !dbg !196
  %10 = load i8*, i8** %p2, align 8, !dbg !197
  %add.ptr3 = getelementptr inbounds i8, i8* %10, i64 %8, !dbg !197
  store i8* %add.ptr3, i8** %p2, align 8, !dbg !197
  br label %sw.epilog, !dbg !198

sw.bb4:                                           ; preds = %entry
  %11 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !199
  %end = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %11, i32 0, i32 2, !dbg !200
  %12 = load i8*, i8** %end, align 8, !dbg !200
  %13 = load i64, i64* %offset.addr, align 8, !dbg !201
  %add.ptr5 = getelementptr inbounds i8, i8* %12, i64 %13, !dbg !202
  %14 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !203
  %p6 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %14, i32 0, i32 1, !dbg !204
  store i8* %add.ptr5, i8** %p6, align 8, !dbg !205
  br label %sw.epilog, !dbg !206

sw.default:                                       ; preds = %entry
  store i64 -30, i64* %retval, align 8, !dbg !207
  br label %return, !dbg !207

sw.epilog:                                        ; preds = %sw.bb4, %sw.bb1, %sw.bb
  %15 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !208
  %p7 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %15, i32 0, i32 1, !dbg !210
  %16 = load i8*, i8** %p7, align 8, !dbg !210
  %17 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !211
  %start8 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %17, i32 0, i32 0, !dbg !212
  %18 = load i8*, i8** %start8, align 8, !dbg !212
  %cmp = icmp ult i8* %16, %18, !dbg !213
  br i1 %cmp, label %if.then, label %if.end, !dbg !214

if.then:                                          ; preds = %sw.epilog
  %19 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !215
  %start9 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %19, i32 0, i32 0, !dbg !217
  %20 = load i8*, i8** %start9, align 8, !dbg !217
  %21 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !218
  %p10 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %21, i32 0, i32 1, !dbg !219
  store i8* %20, i8** %p10, align 8, !dbg !220
  store i64 -25, i64* %retval, align 8, !dbg !221
  br label %return, !dbg !221

if.end:                                           ; preds = %sw.epilog
  %22 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !222
  %p11 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %22, i32 0, i32 1, !dbg !224
  %23 = load i8*, i8** %p11, align 8, !dbg !224
  %24 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !225
  %end12 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %24, i32 0, i32 2, !dbg !226
  %25 = load i8*, i8** %end12, align 8, !dbg !226
  %cmp13 = icmp ugt i8* %23, %25, !dbg !227
  br i1 %cmp13, label %if.then14, label %if.end17, !dbg !228

if.then14:                                        ; preds = %if.end
  %26 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !229
  %end15 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %26, i32 0, i32 2, !dbg !231
  %27 = load i8*, i8** %end15, align 8, !dbg !231
  %28 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !232
  %p16 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %28, i32 0, i32 1, !dbg !233
  store i8* %27, i8** %p16, align 8, !dbg !234
  store i64 -25, i64* %retval, align 8, !dbg !235
  br label %return, !dbg !235

if.end17:                                         ; preds = %if.end
  %29 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !236
  %p18 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %29, i32 0, i32 1, !dbg !237
  %30 = load i8*, i8** %p18, align 8, !dbg !237
  %31 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !238
  %start19 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %31, i32 0, i32 0, !dbg !239
  %32 = load i8*, i8** %start19, align 8, !dbg !239
  %sub.ptr.lhs.cast = ptrtoint i8* %30 to i64, !dbg !240
  %sub.ptr.rhs.cast = ptrtoint i8* %32 to i64, !dbg !240
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !240
  store i64 %sub.ptr.sub, i64* %retval, align 8, !dbg !241
  br label %return, !dbg !241

return:                                           ; preds = %if.end17, %if.then14, %if.then, %sw.default
  %33 = load i64, i64* %retval, align 8, !dbg !242
  ret i64 %33, !dbg !242
}

declare i32 @archive_read_set_skip_callback(%struct.archive*, i64 (%struct.archive*, i8*, i64)*) #3

; Function Attrs: nounwind uwtable
define internal i64 @memory_read_skip(%struct.archive* %a, i8* %client_data, i64 %skip) #0 !dbg !45 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %skip.addr = alloca i64, align 8
  %mine = alloca %struct.read_memory_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !243, metadata !56), !dbg !244
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !245, metadata !56), !dbg !246
  store i64 %skip, i64* %skip.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %skip.addr, metadata !247, metadata !56), !dbg !248
  call void @llvm.dbg.declare(metadata %struct.read_memory_data** %mine, metadata !249, metadata !56), !dbg !250
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !251
  %1 = bitcast i8* %0 to %struct.read_memory_data*, !dbg !252
  store %struct.read_memory_data* %1, %struct.read_memory_data** %mine, align 8, !dbg !250
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !253
  %3 = load i64, i64* %skip.addr, align 8, !dbg !254
  %4 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !256
  %end = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %4, i32 0, i32 2, !dbg !257
  %5 = load i8*, i8** %end, align 8, !dbg !257
  %6 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !258
  %p = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %6, i32 0, i32 1, !dbg !259
  %7 = load i8*, i8** %p, align 8, !dbg !259
  %sub.ptr.lhs.cast = ptrtoint i8* %5 to i64, !dbg !260
  %sub.ptr.rhs.cast = ptrtoint i8* %7 to i64, !dbg !260
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !260
  %cmp = icmp sgt i64 %3, %sub.ptr.sub, !dbg !261
  br i1 %cmp, label %if.then, label %if.end, !dbg !262

if.then:                                          ; preds = %entry
  %8 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !263
  %end1 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %8, i32 0, i32 2, !dbg !264
  %9 = load i8*, i8** %end1, align 8, !dbg !264
  %10 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !265
  %p2 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %10, i32 0, i32 1, !dbg !266
  %11 = load i8*, i8** %p2, align 8, !dbg !266
  %sub.ptr.lhs.cast3 = ptrtoint i8* %9 to i64, !dbg !267
  %sub.ptr.rhs.cast4 = ptrtoint i8* %11 to i64, !dbg !267
  %sub.ptr.sub5 = sub i64 %sub.ptr.lhs.cast3, %sub.ptr.rhs.cast4, !dbg !267
  store i64 %sub.ptr.sub5, i64* %skip.addr, align 8, !dbg !268
  br label %if.end, !dbg !269

if.end:                                           ; preds = %if.then, %entry
  %12 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !270
  %read_size = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %12, i32 0, i32 3, !dbg !271
  %13 = load i64, i64* %read_size, align 8, !dbg !271
  %14 = load i64, i64* %skip.addr, align 8, !dbg !272
  %div = sdiv i64 %14, %13, !dbg !272
  store i64 %div, i64* %skip.addr, align 8, !dbg !272
  %15 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !273
  %read_size6 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %15, i32 0, i32 3, !dbg !274
  %16 = load i64, i64* %read_size6, align 8, !dbg !274
  %17 = load i64, i64* %skip.addr, align 8, !dbg !275
  %mul = mul nsw i64 %17, %16, !dbg !275
  store i64 %mul, i64* %skip.addr, align 8, !dbg !275
  %18 = load i64, i64* %skip.addr, align 8, !dbg !276
  %19 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !277
  %p7 = getelementptr inbounds %struct.read_memory_data, %struct.read_memory_data* %19, i32 0, i32 1, !dbg !278
  %20 = load i8*, i8** %p7, align 8, !dbg !279
  %add.ptr = getelementptr inbounds i8, i8* %20, i64 %18, !dbg !279
  store i8* %add.ptr, i8** %p7, align 8, !dbg !279
  %21 = load i64, i64* %skip.addr, align 8, !dbg !280
  ret i64 %21, !dbg !281
}

declare i32 @archive_read_set_close_callback(%struct.archive*, i32 (%struct.archive*, i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i32 @memory_read_close(%struct.archive* %a, i8* %client_data) #0 !dbg !51 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.read_memory_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !282, metadata !56), !dbg !283
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !284, metadata !56), !dbg !285
  call void @llvm.dbg.declare(metadata %struct.read_memory_data** %mine, metadata !286, metadata !56), !dbg !287
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !288
  %1 = bitcast i8* %0 to %struct.read_memory_data*, !dbg !289
  store %struct.read_memory_data* %1, %struct.read_memory_data** %mine, align 8, !dbg !287
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !290
  %3 = load %struct.read_memory_data*, %struct.read_memory_data** %mine, align 8, !dbg !291
  %4 = bitcast %struct.read_memory_data* %3 to i8*, !dbg !291
  call void @free(i8* %4) #4, !dbg !292
  ret i32 0, !dbg !293
}

declare i32 @archive_read_set_callback_data(%struct.archive*, i8*) #3

declare i32 @archive_read_open1(%struct.archive*) #3

; Function Attrs: nounwind
declare void @free(i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!52, !53}
!llvm.ident = !{!54}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !22)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_open_memory.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !19, !8, !20}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "read_memory_data", file: !1, line: 43, size: 256, align: 64, elements: !6)
!6 = !{!7, !11, !12, !13}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !5, file: !1, line: 44, baseType: !8, size: 64, align: 64)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !10)
!10 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!11 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !5, file: !1, line: 45, baseType: !8, size: 64, align: 64, offset: 64)
!12 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !5, file: !1, line: 46, baseType: !8, size: 64, align: 64, offset: 128)
!13 = !DIDerivedType(tag: DW_TAG_member, name: "read_size", scope: !5, file: !1, line: 47, baseType: !14, size: 64, align: 64, offset: 192)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !15, line: 109, baseType: !16)
!15 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !17, line: 172, baseType: !18)
!17 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !21, line: 40, baseType: !18)
!21 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!22 = !{!23, !35, !38, !41, !45, !48, !51}
!23 = distinct !DISubprogram(name: "archive_read_open_memory", scope: !1, file: !1, line: 57, type: !24, isLocal: false, isDefinition: true, scopeLine: 58, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!24 = !DISubroutineType(types: !25)
!25 = !{!26, !27, !30, !32}
!26 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !29, line: 179, flags: DIFlagFwdDecl)
!29 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !33, line: 62, baseType: !34)
!33 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!34 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!35 = distinct !DISubprogram(name: "archive_read_open_memory2", scope: !1, file: !1, line: 68, type: !36, isLocal: false, isDefinition: true, scopeLine: 70, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!36 = !DISubroutineType(types: !37)
!37 = !{!26, !27, !30, !32, !32}
!38 = distinct !DISubprogram(name: "memory_read_open", scope: !1, file: !1, line: 94, type: !39, isLocal: true, isDefinition: true, scopeLine: 95, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!39 = !DISubroutineType(types: !40)
!40 = !{!26, !27, !19}
!41 = distinct !DISubprogram(name: "memory_read", scope: !1, file: !1, line: 109, type: !42, isLocal: true, isDefinition: true, scopeLine: 110, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!42 = !DISubroutineType(types: !43)
!43 = !{!14, !27, !19, !44}
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!45 = distinct !DISubprogram(name: "memory_read_skip", scope: !1, file: !1, line: 129, type: !46, isLocal: true, isDefinition: true, scopeLine: 130, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!46 = !DISubroutineType(types: !47)
!47 = !{!20, !27, !19, !20}
!48 = distinct !DISubprogram(name: "memory_read_seek", scope: !1, file: !1, line: 147, type: !49, isLocal: true, isDefinition: true, scopeLine: 148, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!49 = !DISubroutineType(types: !50)
!50 = !{!20, !27, !19, !20, !26}
!51 = distinct !DISubprogram(name: "memory_read_close", scope: !1, file: !1, line: 180, type: !39, isLocal: true, isDefinition: true, scopeLine: 181, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!52 = !{i32 2, !"Dwarf Version", i32 4}
!53 = !{i32 2, !"Debug Info Version", i32 3}
!54 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!55 = !DILocalVariable(name: "a", arg: 1, scope: !23, file: !1, line: 57, type: !27)
!56 = !DIExpression()
!57 = !DILocation(line: 57, column: 42, scope: !23)
!58 = !DILocalVariable(name: "buff", arg: 2, scope: !23, file: !1, line: 57, type: !30)
!59 = !DILocation(line: 57, column: 57, scope: !23)
!60 = !DILocalVariable(name: "size", arg: 3, scope: !23, file: !1, line: 57, type: !32)
!61 = !DILocation(line: 57, column: 70, scope: !23)
!62 = !DILocation(line: 59, column: 35, scope: !23)
!63 = !DILocation(line: 59, column: 38, scope: !23)
!64 = !DILocation(line: 59, column: 44, scope: !23)
!65 = !DILocation(line: 59, column: 50, scope: !23)
!66 = !DILocation(line: 59, column: 9, scope: !23)
!67 = !DILocation(line: 59, column: 2, scope: !23)
!68 = !DILocalVariable(name: "a", arg: 1, scope: !35, file: !1, line: 68, type: !27)
!69 = !DILocation(line: 68, column: 43, scope: !35)
!70 = !DILocalVariable(name: "buff", arg: 2, scope: !35, file: !1, line: 68, type: !30)
!71 = !DILocation(line: 68, column: 58, scope: !35)
!72 = !DILocalVariable(name: "size", arg: 3, scope: !35, file: !1, line: 69, type: !32)
!73 = !DILocation(line: 69, column: 12, scope: !35)
!74 = !DILocalVariable(name: "read_size", arg: 4, scope: !35, file: !1, line: 69, type: !32)
!75 = !DILocation(line: 69, column: 25, scope: !35)
!76 = !DILocalVariable(name: "mine", scope: !35, file: !1, line: 71, type: !4)
!77 = !DILocation(line: 71, column: 27, scope: !35)
!78 = !DILocation(line: 73, column: 36, scope: !35)
!79 = !DILocation(line: 73, column: 9, scope: !35)
!80 = !DILocation(line: 73, column: 7, scope: !35)
!81 = !DILocation(line: 74, column: 6, scope: !82)
!82 = distinct !DILexicalBlock(scope: !35, file: !1, line: 74, column: 6)
!83 = !DILocation(line: 74, column: 11, scope: !82)
!84 = !DILocation(line: 74, column: 6, scope: !35)
!85 = !DILocation(line: 75, column: 21, scope: !86)
!86 = distinct !DILexicalBlock(scope: !82, file: !1, line: 74, column: 20)
!87 = !DILocation(line: 75, column: 3, scope: !86)
!88 = !DILocation(line: 76, column: 3, scope: !86)
!89 = !DILocation(line: 78, column: 49, scope: !35)
!90 = !DILocation(line: 78, column: 16, scope: !35)
!91 = !DILocation(line: 78, column: 22, scope: !35)
!92 = !DILocation(line: 78, column: 24, scope: !35)
!93 = !DILocation(line: 78, column: 2, scope: !35)
!94 = !DILocation(line: 78, column: 8, scope: !35)
!95 = !DILocation(line: 78, column: 14, scope: !35)
!96 = !DILocation(line: 79, column: 14, scope: !35)
!97 = !DILocation(line: 79, column: 20, scope: !35)
!98 = !DILocation(line: 79, column: 28, scope: !35)
!99 = !DILocation(line: 79, column: 26, scope: !35)
!100 = !DILocation(line: 79, column: 2, scope: !35)
!101 = !DILocation(line: 79, column: 8, scope: !35)
!102 = !DILocation(line: 79, column: 12, scope: !35)
!103 = !DILocation(line: 80, column: 20, scope: !35)
!104 = !DILocation(line: 80, column: 2, scope: !35)
!105 = !DILocation(line: 80, column: 8, scope: !35)
!106 = !DILocation(line: 80, column: 18, scope: !35)
!107 = !DILocation(line: 81, column: 33, scope: !35)
!108 = !DILocation(line: 81, column: 2, scope: !35)
!109 = !DILocation(line: 82, column: 33, scope: !35)
!110 = !DILocation(line: 82, column: 2, scope: !35)
!111 = !DILocation(line: 83, column: 33, scope: !35)
!112 = !DILocation(line: 83, column: 2, scope: !35)
!113 = !DILocation(line: 84, column: 33, scope: !35)
!114 = !DILocation(line: 84, column: 2, scope: !35)
!115 = !DILocation(line: 85, column: 34, scope: !35)
!116 = !DILocation(line: 85, column: 2, scope: !35)
!117 = !DILocation(line: 86, column: 33, scope: !35)
!118 = !DILocation(line: 86, column: 36, scope: !35)
!119 = !DILocation(line: 86, column: 2, scope: !35)
!120 = !DILocation(line: 87, column: 29, scope: !35)
!121 = !DILocation(line: 87, column: 10, scope: !35)
!122 = !DILocation(line: 87, column: 2, scope: !35)
!123 = !DILocation(line: 88, column: 1, scope: !35)
!124 = !DILocalVariable(name: "a", arg: 1, scope: !38, file: !1, line: 94, type: !27)
!125 = !DILocation(line: 94, column: 34, scope: !38)
!126 = !DILocalVariable(name: "client_data", arg: 2, scope: !38, file: !1, line: 94, type: !19)
!127 = !DILocation(line: 94, column: 43, scope: !38)
!128 = !DILocation(line: 96, column: 8, scope: !38)
!129 = !DILocation(line: 97, column: 8, scope: !38)
!130 = !DILocation(line: 98, column: 2, scope: !38)
!131 = !DILocalVariable(name: "a", arg: 1, scope: !41, file: !1, line: 109, type: !27)
!132 = !DILocation(line: 109, column: 29, scope: !41)
!133 = !DILocalVariable(name: "client_data", arg: 2, scope: !41, file: !1, line: 109, type: !19)
!134 = !DILocation(line: 109, column: 38, scope: !41)
!135 = !DILocalVariable(name: "buff", arg: 3, scope: !41, file: !1, line: 109, type: !44)
!136 = !DILocation(line: 109, column: 64, scope: !41)
!137 = !DILocalVariable(name: "mine", scope: !41, file: !1, line: 111, type: !4)
!138 = !DILocation(line: 111, column: 27, scope: !41)
!139 = !DILocation(line: 111, column: 61, scope: !41)
!140 = !DILocation(line: 111, column: 34, scope: !41)
!141 = !DILocalVariable(name: "size", scope: !41, file: !1, line: 112, type: !14)
!142 = !DILocation(line: 112, column: 10, scope: !41)
!143 = !DILocation(line: 114, column: 8, scope: !41)
!144 = !DILocation(line: 115, column: 10, scope: !41)
!145 = !DILocation(line: 115, column: 16, scope: !41)
!146 = !DILocation(line: 115, column: 3, scope: !41)
!147 = !DILocation(line: 115, column: 8, scope: !41)
!148 = !DILocation(line: 116, column: 9, scope: !41)
!149 = !DILocation(line: 116, column: 15, scope: !41)
!150 = !DILocation(line: 116, column: 21, scope: !41)
!151 = !DILocation(line: 116, column: 27, scope: !41)
!152 = !DILocation(line: 116, column: 19, scope: !41)
!153 = !DILocation(line: 116, column: 7, scope: !41)
!154 = !DILocation(line: 117, column: 6, scope: !155)
!155 = distinct !DILexicalBlock(scope: !41, file: !1, line: 117, column: 6)
!156 = !DILocation(line: 117, column: 13, scope: !155)
!157 = !DILocation(line: 117, column: 19, scope: !155)
!158 = !DILocation(line: 117, column: 11, scope: !155)
!159 = !DILocation(line: 117, column: 6, scope: !41)
!160 = !DILocation(line: 118, column: 10, scope: !155)
!161 = !DILocation(line: 118, column: 16, scope: !155)
!162 = !DILocation(line: 118, column: 8, scope: !155)
!163 = !DILocation(line: 118, column: 3, scope: !155)
!164 = !DILocation(line: 119, column: 20, scope: !41)
!165 = !DILocation(line: 119, column: 9, scope: !41)
!166 = !DILocation(line: 119, column: 15, scope: !41)
!167 = !DILocation(line: 119, column: 17, scope: !41)
!168 = !DILocation(line: 120, column: 10, scope: !41)
!169 = !DILocation(line: 120, column: 2, scope: !41)
!170 = !DILocalVariable(name: "a", arg: 1, scope: !48, file: !1, line: 147, type: !27)
!171 = !DILocation(line: 147, column: 34, scope: !48)
!172 = !DILocalVariable(name: "client_data", arg: 2, scope: !48, file: !1, line: 147, type: !19)
!173 = !DILocation(line: 147, column: 43, scope: !48)
!174 = !DILocalVariable(name: "offset", arg: 3, scope: !48, file: !1, line: 147, type: !20)
!175 = !DILocation(line: 147, column: 64, scope: !48)
!176 = !DILocalVariable(name: "whence", arg: 4, scope: !48, file: !1, line: 147, type: !26)
!177 = !DILocation(line: 147, column: 76, scope: !48)
!178 = !DILocalVariable(name: "mine", scope: !48, file: !1, line: 149, type: !4)
!179 = !DILocation(line: 149, column: 27, scope: !48)
!180 = !DILocation(line: 149, column: 61, scope: !48)
!181 = !DILocation(line: 149, column: 34, scope: !48)
!182 = !DILocation(line: 151, column: 8, scope: !48)
!183 = !DILocation(line: 152, column: 10, scope: !48)
!184 = !DILocation(line: 152, column: 2, scope: !48)
!185 = !DILocation(line: 154, column: 13, scope: !186)
!186 = distinct !DILexicalBlock(scope: !48, file: !1, line: 152, column: 18)
!187 = !DILocation(line: 154, column: 19, scope: !186)
!188 = !DILocation(line: 154, column: 27, scope: !186)
!189 = !DILocation(line: 154, column: 25, scope: !186)
!190 = !DILocation(line: 154, column: 3, scope: !186)
!191 = !DILocation(line: 154, column: 9, scope: !186)
!192 = !DILocation(line: 154, column: 11, scope: !186)
!193 = !DILocation(line: 155, column: 3, scope: !186)
!194 = !DILocation(line: 157, column: 14, scope: !186)
!195 = !DILocation(line: 157, column: 3, scope: !186)
!196 = !DILocation(line: 157, column: 9, scope: !186)
!197 = !DILocation(line: 157, column: 11, scope: !186)
!198 = !DILocation(line: 158, column: 3, scope: !186)
!199 = !DILocation(line: 160, column: 13, scope: !186)
!200 = !DILocation(line: 160, column: 19, scope: !186)
!201 = !DILocation(line: 160, column: 25, scope: !186)
!202 = !DILocation(line: 160, column: 23, scope: !186)
!203 = !DILocation(line: 160, column: 3, scope: !186)
!204 = !DILocation(line: 160, column: 9, scope: !186)
!205 = !DILocation(line: 160, column: 11, scope: !186)
!206 = !DILocation(line: 161, column: 3, scope: !186)
!207 = !DILocation(line: 163, column: 3, scope: !186)
!208 = !DILocation(line: 165, column: 6, scope: !209)
!209 = distinct !DILexicalBlock(scope: !48, file: !1, line: 165, column: 6)
!210 = !DILocation(line: 165, column: 12, scope: !209)
!211 = !DILocation(line: 165, column: 16, scope: !209)
!212 = !DILocation(line: 165, column: 22, scope: !209)
!213 = !DILocation(line: 165, column: 14, scope: !209)
!214 = !DILocation(line: 165, column: 6, scope: !48)
!215 = !DILocation(line: 166, column: 13, scope: !216)
!216 = distinct !DILexicalBlock(scope: !209, file: !1, line: 165, column: 29)
!217 = !DILocation(line: 166, column: 19, scope: !216)
!218 = !DILocation(line: 166, column: 3, scope: !216)
!219 = !DILocation(line: 166, column: 9, scope: !216)
!220 = !DILocation(line: 166, column: 11, scope: !216)
!221 = !DILocation(line: 167, column: 3, scope: !216)
!222 = !DILocation(line: 169, column: 6, scope: !223)
!223 = distinct !DILexicalBlock(scope: !48, file: !1, line: 169, column: 6)
!224 = !DILocation(line: 169, column: 12, scope: !223)
!225 = !DILocation(line: 169, column: 16, scope: !223)
!226 = !DILocation(line: 169, column: 22, scope: !223)
!227 = !DILocation(line: 169, column: 14, scope: !223)
!228 = !DILocation(line: 169, column: 6, scope: !48)
!229 = !DILocation(line: 170, column: 13, scope: !230)
!230 = distinct !DILexicalBlock(scope: !223, file: !1, line: 169, column: 27)
!231 = !DILocation(line: 170, column: 19, scope: !230)
!232 = !DILocation(line: 170, column: 3, scope: !230)
!233 = !DILocation(line: 170, column: 9, scope: !230)
!234 = !DILocation(line: 170, column: 11, scope: !230)
!235 = !DILocation(line: 171, column: 3, scope: !230)
!236 = !DILocation(line: 173, column: 10, scope: !48)
!237 = !DILocation(line: 173, column: 16, scope: !48)
!238 = !DILocation(line: 173, column: 20, scope: !48)
!239 = !DILocation(line: 173, column: 26, scope: !48)
!240 = !DILocation(line: 173, column: 18, scope: !48)
!241 = !DILocation(line: 173, column: 2, scope: !48)
!242 = !DILocation(line: 174, column: 1, scope: !48)
!243 = !DILocalVariable(name: "a", arg: 1, scope: !45, file: !1, line: 129, type: !27)
!244 = !DILocation(line: 129, column: 34, scope: !45)
!245 = !DILocalVariable(name: "client_data", arg: 2, scope: !45, file: !1, line: 129, type: !19)
!246 = !DILocation(line: 129, column: 43, scope: !45)
!247 = !DILocalVariable(name: "skip", arg: 3, scope: !45, file: !1, line: 129, type: !20)
!248 = !DILocation(line: 129, column: 64, scope: !45)
!249 = !DILocalVariable(name: "mine", scope: !45, file: !1, line: 131, type: !4)
!250 = !DILocation(line: 131, column: 27, scope: !45)
!251 = !DILocation(line: 131, column: 61, scope: !45)
!252 = !DILocation(line: 131, column: 34, scope: !45)
!253 = !DILocation(line: 133, column: 8, scope: !45)
!254 = !DILocation(line: 134, column: 15, scope: !255)
!255 = distinct !DILexicalBlock(scope: !45, file: !1, line: 134, column: 6)
!256 = !DILocation(line: 134, column: 32, scope: !255)
!257 = !DILocation(line: 134, column: 38, scope: !255)
!258 = !DILocation(line: 134, column: 44, scope: !255)
!259 = !DILocation(line: 134, column: 50, scope: !255)
!260 = !DILocation(line: 134, column: 42, scope: !255)
!261 = !DILocation(line: 134, column: 20, scope: !255)
!262 = !DILocation(line: 134, column: 6, scope: !45)
!263 = !DILocation(line: 135, column: 10, scope: !255)
!264 = !DILocation(line: 135, column: 16, scope: !255)
!265 = !DILocation(line: 135, column: 22, scope: !255)
!266 = !DILocation(line: 135, column: 28, scope: !255)
!267 = !DILocation(line: 135, column: 20, scope: !255)
!268 = !DILocation(line: 135, column: 8, scope: !255)
!269 = !DILocation(line: 135, column: 3, scope: !255)
!270 = !DILocation(line: 137, column: 10, scope: !45)
!271 = !DILocation(line: 137, column: 16, scope: !45)
!272 = !DILocation(line: 137, column: 7, scope: !45)
!273 = !DILocation(line: 138, column: 10, scope: !45)
!274 = !DILocation(line: 138, column: 16, scope: !45)
!275 = !DILocation(line: 138, column: 7, scope: !45)
!276 = !DILocation(line: 139, column: 13, scope: !45)
!277 = !DILocation(line: 139, column: 2, scope: !45)
!278 = !DILocation(line: 139, column: 8, scope: !45)
!279 = !DILocation(line: 139, column: 10, scope: !45)
!280 = !DILocation(line: 140, column: 10, scope: !45)
!281 = !DILocation(line: 140, column: 2, scope: !45)
!282 = !DILocalVariable(name: "a", arg: 1, scope: !51, file: !1, line: 180, type: !27)
!283 = !DILocation(line: 180, column: 35, scope: !51)
!284 = !DILocalVariable(name: "client_data", arg: 2, scope: !51, file: !1, line: 180, type: !19)
!285 = !DILocation(line: 180, column: 44, scope: !51)
!286 = !DILocalVariable(name: "mine", scope: !51, file: !1, line: 182, type: !4)
!287 = !DILocation(line: 182, column: 27, scope: !51)
!288 = !DILocation(line: 182, column: 61, scope: !51)
!289 = !DILocation(line: 182, column: 34, scope: !51)
!290 = !DILocation(line: 183, column: 8, scope: !51)
!291 = !DILocation(line: 184, column: 7, scope: !51)
!292 = !DILocation(line: 184, column: 2, scope: !51)
!293 = !DILocation(line: 185, column: 2, scope: !51)
