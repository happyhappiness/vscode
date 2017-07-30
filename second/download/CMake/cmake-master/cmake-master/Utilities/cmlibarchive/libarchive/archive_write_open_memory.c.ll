; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_open_memory.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque
%struct.write_memory_data = type { i64, i64, i64*, i8* }

@.str = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.1 = private unnamed_addr constant [17 x i8] c"Buffer exhausted\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_open_memory(%struct.archive* %a, i8* %buff, i64 %buffSize, i64* %used) #0 !dbg !19 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %buffSize.addr = alloca i64, align 8
  %used.addr = alloca i64*, align 8
  %mine = alloca %struct.write_memory_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !43, metadata !44), !dbg !45
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !46, metadata !44), !dbg !47
  store i64 %buffSize, i64* %buffSize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %buffSize.addr, metadata !48, metadata !44), !dbg !49
  store i64* %used, i64** %used.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %used.addr, metadata !50, metadata !44), !dbg !51
  call void @llvm.dbg.declare(metadata %struct.write_memory_data** %mine, metadata !52, metadata !44), !dbg !53
  %call = call noalias i8* @calloc(i64 1, i64 32) #5, !dbg !54
  %0 = bitcast i8* %call to %struct.write_memory_data*, !dbg !55
  store %struct.write_memory_data* %0, %struct.write_memory_data** %mine, align 8, !dbg !56
  %1 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !57
  %cmp = icmp eq %struct.write_memory_data* %1, null, !dbg !59
  br i1 %cmp, label %if.then, label %if.end, !dbg !60

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !61
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %2, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !63
  store i32 -30, i32* %retval, align 4, !dbg !64
  br label %return, !dbg !64

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %buff.addr, align 8, !dbg !65
  %4 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !66
  %buff1 = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %4, i32 0, i32 3, !dbg !67
  store i8* %3, i8** %buff1, align 8, !dbg !68
  %5 = load i64, i64* %buffSize.addr, align 8, !dbg !69
  %6 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !70
  %size = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %6, i32 0, i32 1, !dbg !71
  store i64 %5, i64* %size, align 8, !dbg !72
  %7 = load i64*, i64** %used.addr, align 8, !dbg !73
  %8 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !74
  %client_size = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %8, i32 0, i32 2, !dbg !75
  store i64* %7, i64** %client_size, align 8, !dbg !76
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !77
  %10 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !78
  %11 = bitcast %struct.write_memory_data* %10 to i8*, !dbg !78
  %call2 = call i32 @archive_write_open(%struct.archive* %9, i8* %11, i32 (%struct.archive*, i8*)* @memory_write_open, i64 (%struct.archive*, i8*, i8*, i64)* @memory_write, i32 (%struct.archive*, i8*)* @memory_write_close), !dbg !79
  store i32 %call2, i32* %retval, align 4, !dbg !80
  br label %return, !dbg !80

return:                                           ; preds = %if.end, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !81
  ret i32 %12, !dbg !81
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

declare i32 @archive_write_open(%struct.archive*, i8*, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i32 @memory_write_open(%struct.archive* %a, i8* %client_data) #0 !dbg !26 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.write_memory_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !82, metadata !44), !dbg !83
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !84, metadata !44), !dbg !85
  call void @llvm.dbg.declare(metadata %struct.write_memory_data** %mine, metadata !86, metadata !44), !dbg !87
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !88
  %1 = bitcast i8* %0 to %struct.write_memory_data*, !dbg !88
  store %struct.write_memory_data* %1, %struct.write_memory_data** %mine, align 8, !dbg !89
  %2 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !90
  %used = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %2, i32 0, i32 0, !dbg !91
  store i64 0, i64* %used, align 8, !dbg !92
  %3 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !93
  %client_size = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %3, i32 0, i32 2, !dbg !95
  %4 = load i64*, i64** %client_size, align 8, !dbg !95
  %cmp = icmp ne i64* %4, null, !dbg !96
  br i1 %cmp, label %if.then, label %if.end, !dbg !97

if.then:                                          ; preds = %entry
  %5 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !98
  %used1 = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %5, i32 0, i32 0, !dbg !99
  %6 = load i64, i64* %used1, align 8, !dbg !99
  %7 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !100
  %client_size2 = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %7, i32 0, i32 2, !dbg !101
  %8 = load i64*, i64** %client_size2, align 8, !dbg !101
  store i64 %6, i64* %8, align 8, !dbg !102
  br label %if.end, !dbg !103

if.end:                                           ; preds = %if.then, %entry
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !104
  %call = call i32 @archive_write_get_bytes_in_last_block(%struct.archive* %9), !dbg !106
  %cmp3 = icmp eq i32 -1, %call, !dbg !107
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !108

if.then4:                                         ; preds = %if.end
  %10 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !109
  %call5 = call i32 @archive_write_set_bytes_in_last_block(%struct.archive* %10, i32 1), !dbg !110
  br label %if.end6, !dbg !110

if.end6:                                          ; preds = %if.then4, %if.end
  ret i32 0, !dbg !111
}

; Function Attrs: nounwind uwtable
define internal i64 @memory_write(%struct.archive* %a, i8* %client_data, i8* %buff, i64 %length) #0 !dbg !29 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %mine = alloca %struct.write_memory_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !112, metadata !44), !dbg !113
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !114, metadata !44), !dbg !115
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !116, metadata !44), !dbg !117
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !118, metadata !44), !dbg !119
  call void @llvm.dbg.declare(metadata %struct.write_memory_data** %mine, metadata !120, metadata !44), !dbg !121
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !122
  %1 = bitcast i8* %0 to %struct.write_memory_data*, !dbg !122
  store %struct.write_memory_data* %1, %struct.write_memory_data** %mine, align 8, !dbg !123
  %2 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !124
  %used = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %2, i32 0, i32 0, !dbg !126
  %3 = load i64, i64* %used, align 8, !dbg !126
  %4 = load i64, i64* %length.addr, align 8, !dbg !127
  %add = add i64 %3, %4, !dbg !128
  %5 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !129
  %size = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %5, i32 0, i32 1, !dbg !130
  %6 = load i64, i64* %size, align 8, !dbg !130
  %cmp = icmp ugt i64 %add, %6, !dbg !131
  br i1 %cmp, label %if.then, label %if.end, !dbg !132

if.then:                                          ; preds = %entry
  %7 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !133
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %7, i32 12, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.1, i32 0, i32 0)), !dbg !135
  store i64 -30, i64* %retval, align 8, !dbg !136
  br label %return, !dbg !136

if.end:                                           ; preds = %entry
  %8 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !137
  %buff1 = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %8, i32 0, i32 3, !dbg !138
  %9 = load i8*, i8** %buff1, align 8, !dbg !138
  %10 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !139
  %used2 = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %10, i32 0, i32 0, !dbg !140
  %11 = load i64, i64* %used2, align 8, !dbg !140
  %add.ptr = getelementptr inbounds i8, i8* %9, i64 %11, !dbg !141
  %12 = load i8*, i8** %buff.addr, align 8, !dbg !142
  %13 = load i64, i64* %length.addr, align 8, !dbg !143
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %12, i64 %13, i32 1, i1 false), !dbg !144
  %14 = load i64, i64* %length.addr, align 8, !dbg !145
  %15 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !146
  %used3 = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %15, i32 0, i32 0, !dbg !147
  %16 = load i64, i64* %used3, align 8, !dbg !148
  %add4 = add i64 %16, %14, !dbg !148
  store i64 %add4, i64* %used3, align 8, !dbg !148
  %17 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !149
  %client_size = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %17, i32 0, i32 2, !dbg !151
  %18 = load i64*, i64** %client_size, align 8, !dbg !151
  %cmp5 = icmp ne i64* %18, null, !dbg !152
  br i1 %cmp5, label %if.then6, label %if.end9, !dbg !153

if.then6:                                         ; preds = %if.end
  %19 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !154
  %used7 = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %19, i32 0, i32 0, !dbg !155
  %20 = load i64, i64* %used7, align 8, !dbg !155
  %21 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !156
  %client_size8 = getelementptr inbounds %struct.write_memory_data, %struct.write_memory_data* %21, i32 0, i32 2, !dbg !157
  %22 = load i64*, i64** %client_size8, align 8, !dbg !157
  store i64 %20, i64* %22, align 8, !dbg !158
  br label %if.end9, !dbg !159

if.end9:                                          ; preds = %if.then6, %if.end
  %23 = load i64, i64* %length.addr, align 8, !dbg !160
  store i64 %23, i64* %retval, align 8, !dbg !161
  br label %return, !dbg !161

return:                                           ; preds = %if.end9, %if.then
  %24 = load i64, i64* %retval, align 8, !dbg !162
  ret i64 %24, !dbg !162
}

; Function Attrs: nounwind uwtable
define internal i32 @memory_write_close(%struct.archive* %a, i8* %client_data) #0 !dbg !39 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.write_memory_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !163, metadata !44), !dbg !164
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !165, metadata !44), !dbg !166
  call void @llvm.dbg.declare(metadata %struct.write_memory_data** %mine, metadata !167, metadata !44), !dbg !168
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !169
  %1 = load i8*, i8** %client_data.addr, align 8, !dbg !170
  %2 = bitcast i8* %1 to %struct.write_memory_data*, !dbg !170
  store %struct.write_memory_data* %2, %struct.write_memory_data** %mine, align 8, !dbg !171
  %3 = load %struct.write_memory_data*, %struct.write_memory_data** %mine, align 8, !dbg !172
  %4 = bitcast %struct.write_memory_data* %3 to i8*, !dbg !172
  call void @free(i8* %4) #5, !dbg !173
  ret i32 0, !dbg !174
}

declare i32 @archive_write_get_bytes_in_last_block(%struct.archive*) #3

declare i32 @archive_write_set_bytes_in_last_block(%struct.archive*, i32) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind
declare void @free(i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!40, !41}
!llvm.ident = !{!42}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !18)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_open_memory.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !17}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "write_memory_data", file: !1, line: 35, size: 256, align: 64, elements: !6)
!6 = !{!7, !11, !12, !14}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "used", scope: !5, file: !1, line: 36, baseType: !8, size: 64, align: 64)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !9, line: 62, baseType: !10)
!9 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!10 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!11 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !5, file: !1, line: 37, baseType: !8, size: 64, align: 64, offset: 64)
!12 = !DIDerivedType(tag: DW_TAG_member, name: "client_size", scope: !5, file: !1, line: 38, baseType: !13, size: 64, align: 64, offset: 128)
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "buff", scope: !5, file: !1, line: 39, baseType: !15, size: 64, align: 64, offset: 192)
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!16 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!18 = !{!19, !26, !29, !39}
!19 = distinct !DISubprogram(name: "archive_write_open_memory", scope: !1, file: !1, line: 52, type: !20, isLocal: false, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{!22, !23, !17, !8, !13}
!22 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !25, line: 179, flags: DIFlagFwdDecl)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!26 = distinct !DISubprogram(name: "memory_write_open", scope: !1, file: !1, line: 69, type: !27, isLocal: true, isDefinition: true, scopeLine: 70, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!27 = !DISubroutineType(types: !28)
!28 = !{!22, !23, !17}
!29 = distinct !DISubprogram(name: "memory_write", scope: !1, file: !1, line: 89, type: !30, isLocal: true, isDefinition: true, scopeLine: 90, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!30 = !DISubroutineType(types: !31)
!31 = !{!32, !23, !17, !37, !8}
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !33, line: 109, baseType: !34)
!33 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!34 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !35, line: 172, baseType: !36)
!35 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!36 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!37 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!38 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!39 = distinct !DISubprogram(name: "memory_write_close", scope: !1, file: !1, line: 106, type: !27, isLocal: true, isDefinition: true, scopeLine: 107, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!40 = !{i32 2, !"Dwarf Version", i32 4}
!41 = !{i32 2, !"Debug Info Version", i32 3}
!42 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!43 = !DILocalVariable(name: "a", arg: 1, scope: !19, file: !1, line: 52, type: !23)
!44 = !DIExpression()
!45 = !DILocation(line: 52, column: 43, scope: !19)
!46 = !DILocalVariable(name: "buff", arg: 2, scope: !19, file: !1, line: 52, type: !17)
!47 = !DILocation(line: 52, column: 52, scope: !19)
!48 = !DILocalVariable(name: "buffSize", arg: 3, scope: !19, file: !1, line: 52, type: !8)
!49 = !DILocation(line: 52, column: 65, scope: !19)
!50 = !DILocalVariable(name: "used", arg: 4, scope: !19, file: !1, line: 52, type: !13)
!51 = !DILocation(line: 52, column: 83, scope: !19)
!52 = !DILocalVariable(name: "mine", scope: !19, file: !1, line: 54, type: !4)
!53 = !DILocation(line: 54, column: 28, scope: !19)
!54 = !DILocation(line: 56, column: 37, scope: !19)
!55 = !DILocation(line: 56, column: 9, scope: !19)
!56 = !DILocation(line: 56, column: 7, scope: !19)
!57 = !DILocation(line: 57, column: 6, scope: !58)
!58 = distinct !DILexicalBlock(scope: !19, file: !1, line: 57, column: 6)
!59 = !DILocation(line: 57, column: 11, scope: !58)
!60 = !DILocation(line: 57, column: 6, scope: !19)
!61 = !DILocation(line: 58, column: 21, scope: !62)
!62 = distinct !DILexicalBlock(scope: !58, file: !1, line: 57, column: 20)
!63 = !DILocation(line: 58, column: 3, scope: !62)
!64 = !DILocation(line: 59, column: 3, scope: !62)
!65 = !DILocation(line: 61, column: 15, scope: !19)
!66 = !DILocation(line: 61, column: 2, scope: !19)
!67 = !DILocation(line: 61, column: 8, scope: !19)
!68 = !DILocation(line: 61, column: 13, scope: !19)
!69 = !DILocation(line: 62, column: 15, scope: !19)
!70 = !DILocation(line: 62, column: 2, scope: !19)
!71 = !DILocation(line: 62, column: 8, scope: !19)
!72 = !DILocation(line: 62, column: 13, scope: !19)
!73 = !DILocation(line: 63, column: 22, scope: !19)
!74 = !DILocation(line: 63, column: 2, scope: !19)
!75 = !DILocation(line: 63, column: 8, scope: !19)
!76 = !DILocation(line: 63, column: 20, scope: !19)
!77 = !DILocation(line: 64, column: 29, scope: !19)
!78 = !DILocation(line: 64, column: 32, scope: !19)
!79 = !DILocation(line: 64, column: 10, scope: !19)
!80 = !DILocation(line: 64, column: 2, scope: !19)
!81 = !DILocation(line: 66, column: 1, scope: !19)
!82 = !DILocalVariable(name: "a", arg: 1, scope: !26, file: !1, line: 69, type: !23)
!83 = !DILocation(line: 69, column: 35, scope: !26)
!84 = !DILocalVariable(name: "client_data", arg: 2, scope: !26, file: !1, line: 69, type: !17)
!85 = !DILocation(line: 69, column: 44, scope: !26)
!86 = !DILocalVariable(name: "mine", scope: !26, file: !1, line: 71, type: !4)
!87 = !DILocation(line: 71, column: 28, scope: !26)
!88 = !DILocation(line: 72, column: 9, scope: !26)
!89 = !DILocation(line: 72, column: 7, scope: !26)
!90 = !DILocation(line: 73, column: 2, scope: !26)
!91 = !DILocation(line: 73, column: 8, scope: !26)
!92 = !DILocation(line: 73, column: 13, scope: !26)
!93 = !DILocation(line: 74, column: 6, scope: !94)
!94 = distinct !DILexicalBlock(scope: !26, file: !1, line: 74, column: 6)
!95 = !DILocation(line: 74, column: 12, scope: !94)
!96 = !DILocation(line: 74, column: 24, scope: !94)
!97 = !DILocation(line: 74, column: 6, scope: !26)
!98 = !DILocation(line: 75, column: 24, scope: !94)
!99 = !DILocation(line: 75, column: 30, scope: !94)
!100 = !DILocation(line: 75, column: 4, scope: !94)
!101 = !DILocation(line: 75, column: 10, scope: !94)
!102 = !DILocation(line: 75, column: 22, scope: !94)
!103 = !DILocation(line: 75, column: 3, scope: !94)
!104 = !DILocation(line: 77, column: 50, scope: !105)
!105 = distinct !DILexicalBlock(scope: !26, file: !1, line: 77, column: 6)
!106 = !DILocation(line: 77, column: 12, scope: !105)
!107 = !DILocation(line: 77, column: 9, scope: !105)
!108 = !DILocation(line: 77, column: 6, scope: !26)
!109 = !DILocation(line: 78, column: 41, scope: !105)
!110 = !DILocation(line: 78, column: 3, scope: !105)
!111 = !DILocation(line: 79, column: 2, scope: !26)
!112 = !DILocalVariable(name: "a", arg: 1, scope: !29, file: !1, line: 89, type: !23)
!113 = !DILocation(line: 89, column: 30, scope: !29)
!114 = !DILocalVariable(name: "client_data", arg: 2, scope: !29, file: !1, line: 89, type: !17)
!115 = !DILocation(line: 89, column: 39, scope: !29)
!116 = !DILocalVariable(name: "buff", arg: 3, scope: !29, file: !1, line: 89, type: !37)
!117 = !DILocation(line: 89, column: 64, scope: !29)
!118 = !DILocalVariable(name: "length", arg: 4, scope: !29, file: !1, line: 89, type: !8)
!119 = !DILocation(line: 89, column: 77, scope: !29)
!120 = !DILocalVariable(name: "mine", scope: !29, file: !1, line: 91, type: !4)
!121 = !DILocation(line: 91, column: 28, scope: !29)
!122 = !DILocation(line: 92, column: 9, scope: !29)
!123 = !DILocation(line: 92, column: 7, scope: !29)
!124 = !DILocation(line: 94, column: 6, scope: !125)
!125 = distinct !DILexicalBlock(scope: !29, file: !1, line: 94, column: 6)
!126 = !DILocation(line: 94, column: 12, scope: !125)
!127 = !DILocation(line: 94, column: 19, scope: !125)
!128 = !DILocation(line: 94, column: 17, scope: !125)
!129 = !DILocation(line: 94, column: 28, scope: !125)
!130 = !DILocation(line: 94, column: 34, scope: !125)
!131 = !DILocation(line: 94, column: 26, scope: !125)
!132 = !DILocation(line: 94, column: 6, scope: !29)
!133 = !DILocation(line: 95, column: 21, scope: !134)
!134 = distinct !DILexicalBlock(scope: !125, file: !1, line: 94, column: 40)
!135 = !DILocation(line: 95, column: 3, scope: !134)
!136 = !DILocation(line: 96, column: 3, scope: !134)
!137 = !DILocation(line: 98, column: 9, scope: !29)
!138 = !DILocation(line: 98, column: 15, scope: !29)
!139 = !DILocation(line: 98, column: 22, scope: !29)
!140 = !DILocation(line: 98, column: 28, scope: !29)
!141 = !DILocation(line: 98, column: 20, scope: !29)
!142 = !DILocation(line: 98, column: 34, scope: !29)
!143 = !DILocation(line: 98, column: 40, scope: !29)
!144 = !DILocation(line: 98, column: 2, scope: !29)
!145 = !DILocation(line: 99, column: 16, scope: !29)
!146 = !DILocation(line: 99, column: 2, scope: !29)
!147 = !DILocation(line: 99, column: 8, scope: !29)
!148 = !DILocation(line: 99, column: 13, scope: !29)
!149 = !DILocation(line: 100, column: 6, scope: !150)
!150 = distinct !DILexicalBlock(scope: !29, file: !1, line: 100, column: 6)
!151 = !DILocation(line: 100, column: 12, scope: !150)
!152 = !DILocation(line: 100, column: 24, scope: !150)
!153 = !DILocation(line: 100, column: 6, scope: !29)
!154 = !DILocation(line: 101, column: 24, scope: !150)
!155 = !DILocation(line: 101, column: 30, scope: !150)
!156 = !DILocation(line: 101, column: 4, scope: !150)
!157 = !DILocation(line: 101, column: 10, scope: !150)
!158 = !DILocation(line: 101, column: 22, scope: !150)
!159 = !DILocation(line: 101, column: 3, scope: !150)
!160 = !DILocation(line: 102, column: 10, scope: !29)
!161 = !DILocation(line: 102, column: 2, scope: !29)
!162 = !DILocation(line: 103, column: 1, scope: !29)
!163 = !DILocalVariable(name: "a", arg: 1, scope: !39, file: !1, line: 106, type: !23)
!164 = !DILocation(line: 106, column: 36, scope: !39)
!165 = !DILocalVariable(name: "client_data", arg: 2, scope: !39, file: !1, line: 106, type: !17)
!166 = !DILocation(line: 106, column: 45, scope: !39)
!167 = !DILocalVariable(name: "mine", scope: !39, file: !1, line: 108, type: !4)
!168 = !DILocation(line: 108, column: 28, scope: !39)
!169 = !DILocation(line: 109, column: 8, scope: !39)
!170 = !DILocation(line: 110, column: 9, scope: !39)
!171 = !DILocation(line: 110, column: 7, scope: !39)
!172 = !DILocation(line: 111, column: 7, scope: !39)
!173 = !DILocation(line: 111, column: 2, scope: !39)
!174 = !DILocation(line: 112, column: 2, scope: !39)
