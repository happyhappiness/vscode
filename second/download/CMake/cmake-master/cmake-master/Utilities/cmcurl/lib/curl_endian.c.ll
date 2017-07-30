; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_endian.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define zeroext i16 @Curl_read16_le(i8* %buf) #0 !dbg !10 {
entry:
  %buf.addr = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !43, metadata !44), !dbg !45
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !46
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !46
  %1 = load i8, i8* %arrayidx, align 1, !dbg !46
  %conv = zext i8 %1 to i16, !dbg !47
  %conv1 = zext i16 %conv to i32, !dbg !48
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !49
  %arrayidx2 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !49
  %3 = load i8, i8* %arrayidx2, align 1, !dbg !49
  %conv3 = zext i8 %3 to i16, !dbg !50
  %conv4 = zext i16 %conv3 to i32, !dbg !50
  %shl = shl i32 %conv4, 8, !dbg !51
  %or = or i32 %conv1, %shl, !dbg !52
  %conv5 = trunc i32 %or to i16, !dbg !53
  ret i16 %conv5, !dbg !54
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @Curl_read32_le(i8* %buf) #0 !dbg !16 {
entry:
  %buf.addr = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !55, metadata !44), !dbg !56
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !57
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !57
  %1 = load i8, i8* %arrayidx, align 1, !dbg !57
  %conv = zext i8 %1 to i32, !dbg !58
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !59
  %arrayidx1 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !59
  %3 = load i8, i8* %arrayidx1, align 1, !dbg !59
  %conv2 = zext i8 %3 to i32, !dbg !60
  %shl = shl i32 %conv2, 8, !dbg !61
  %or = or i32 %conv, %shl, !dbg !62
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !63
  %arrayidx3 = getelementptr inbounds i8, i8* %4, i64 2, !dbg !63
  %5 = load i8, i8* %arrayidx3, align 1, !dbg !63
  %conv4 = zext i8 %5 to i32, !dbg !64
  %shl5 = shl i32 %conv4, 16, !dbg !65
  %or6 = or i32 %or, %shl5, !dbg !66
  %6 = load i8*, i8** %buf.addr, align 8, !dbg !67
  %arrayidx7 = getelementptr inbounds i8, i8* %6, i64 3, !dbg !67
  %7 = load i8, i8* %arrayidx7, align 1, !dbg !67
  %conv8 = zext i8 %7 to i32, !dbg !68
  %shl9 = shl i32 %conv8, 24, !dbg !69
  %or10 = or i32 %or6, %shl9, !dbg !70
  ret i32 %or10, !dbg !71
}

; Function Attrs: nounwind uwtable
define i64 @Curl_read64_le(i8* %buf) #0 !dbg !19 {
entry:
  %buf.addr = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !72, metadata !44), !dbg !73
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !74
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !74
  %1 = load i8, i8* %arrayidx, align 1, !dbg !74
  %conv = zext i8 %1 to i64, !dbg !75
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !76
  %arrayidx1 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !76
  %3 = load i8, i8* %arrayidx1, align 1, !dbg !76
  %conv2 = zext i8 %3 to i64, !dbg !77
  %shl = shl i64 %conv2, 8, !dbg !78
  %or = or i64 %conv, %shl, !dbg !79
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !80
  %arrayidx3 = getelementptr inbounds i8, i8* %4, i64 2, !dbg !80
  %5 = load i8, i8* %arrayidx3, align 1, !dbg !80
  %conv4 = zext i8 %5 to i64, !dbg !81
  %shl5 = shl i64 %conv4, 16, !dbg !82
  %or6 = or i64 %or, %shl5, !dbg !83
  %6 = load i8*, i8** %buf.addr, align 8, !dbg !84
  %arrayidx7 = getelementptr inbounds i8, i8* %6, i64 3, !dbg !84
  %7 = load i8, i8* %arrayidx7, align 1, !dbg !84
  %conv8 = zext i8 %7 to i64, !dbg !85
  %shl9 = shl i64 %conv8, 24, !dbg !86
  %or10 = or i64 %or6, %shl9, !dbg !87
  %8 = load i8*, i8** %buf.addr, align 8, !dbg !88
  %arrayidx11 = getelementptr inbounds i8, i8* %8, i64 4, !dbg !88
  %9 = load i8, i8* %arrayidx11, align 1, !dbg !88
  %conv12 = zext i8 %9 to i64, !dbg !89
  %shl13 = shl i64 %conv12, 32, !dbg !90
  %or14 = or i64 %or10, %shl13, !dbg !91
  %10 = load i8*, i8** %buf.addr, align 8, !dbg !92
  %arrayidx15 = getelementptr inbounds i8, i8* %10, i64 5, !dbg !92
  %11 = load i8, i8* %arrayidx15, align 1, !dbg !92
  %conv16 = zext i8 %11 to i64, !dbg !93
  %shl17 = shl i64 %conv16, 40, !dbg !94
  %or18 = or i64 %or14, %shl17, !dbg !95
  %12 = load i8*, i8** %buf.addr, align 8, !dbg !96
  %arrayidx19 = getelementptr inbounds i8, i8* %12, i64 6, !dbg !96
  %13 = load i8, i8* %arrayidx19, align 1, !dbg !96
  %conv20 = zext i8 %13 to i64, !dbg !97
  %shl21 = shl i64 %conv20, 48, !dbg !98
  %or22 = or i64 %or18, %shl21, !dbg !99
  %14 = load i8*, i8** %buf.addr, align 8, !dbg !100
  %arrayidx23 = getelementptr inbounds i8, i8* %14, i64 7, !dbg !100
  %15 = load i8, i8* %arrayidx23, align 1, !dbg !100
  %conv24 = zext i8 %15 to i64, !dbg !101
  %shl25 = shl i64 %conv24, 56, !dbg !102
  %or26 = or i64 %or22, %shl25, !dbg !103
  ret i64 %or26, !dbg !104
}

; Function Attrs: nounwind uwtable
define zeroext i16 @Curl_read16_be(i8* %buf) #0 !dbg !22 {
entry:
  %buf.addr = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !105, metadata !44), !dbg !106
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !107
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !107
  %1 = load i8, i8* %arrayidx, align 1, !dbg !107
  %conv = zext i8 %1 to i16, !dbg !108
  %conv1 = zext i16 %conv to i32, !dbg !108
  %shl = shl i32 %conv1, 8, !dbg !109
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !110
  %arrayidx2 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !110
  %3 = load i8, i8* %arrayidx2, align 1, !dbg !110
  %conv3 = zext i8 %3 to i16, !dbg !111
  %conv4 = zext i16 %conv3 to i32, !dbg !112
  %or = or i32 %shl, %conv4, !dbg !113
  %conv5 = trunc i32 %or to i16, !dbg !114
  ret i16 %conv5, !dbg !115
}

; Function Attrs: nounwind uwtable
define i32 @Curl_read32_be(i8* %buf) #0 !dbg !23 {
entry:
  %buf.addr = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !116, metadata !44), !dbg !117
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !118
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !118
  %1 = load i8, i8* %arrayidx, align 1, !dbg !118
  %conv = zext i8 %1 to i32, !dbg !119
  %shl = shl i32 %conv, 24, !dbg !120
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !121
  %arrayidx1 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !121
  %3 = load i8, i8* %arrayidx1, align 1, !dbg !121
  %conv2 = zext i8 %3 to i32, !dbg !122
  %shl3 = shl i32 %conv2, 16, !dbg !123
  %or = or i32 %shl, %shl3, !dbg !124
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !125
  %arrayidx4 = getelementptr inbounds i8, i8* %4, i64 2, !dbg !125
  %5 = load i8, i8* %arrayidx4, align 1, !dbg !125
  %conv5 = zext i8 %5 to i32, !dbg !126
  %shl6 = shl i32 %conv5, 8, !dbg !127
  %or7 = or i32 %or, %shl6, !dbg !128
  %6 = load i8*, i8** %buf.addr, align 8, !dbg !129
  %arrayidx8 = getelementptr inbounds i8, i8* %6, i64 3, !dbg !129
  %7 = load i8, i8* %arrayidx8, align 1, !dbg !129
  %conv9 = zext i8 %7 to i32, !dbg !130
  %or10 = or i32 %or7, %conv9, !dbg !131
  ret i32 %or10, !dbg !132
}

; Function Attrs: nounwind uwtable
define i64 @Curl_read64_be(i8* %buf) #0 !dbg !24 {
entry:
  %buf.addr = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !133, metadata !44), !dbg !134
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !135
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !135
  %1 = load i8, i8* %arrayidx, align 1, !dbg !135
  %conv = zext i8 %1 to i64, !dbg !136
  %shl = shl i64 %conv, 56, !dbg !137
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !138
  %arrayidx1 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !138
  %3 = load i8, i8* %arrayidx1, align 1, !dbg !138
  %conv2 = zext i8 %3 to i64, !dbg !139
  %shl3 = shl i64 %conv2, 48, !dbg !140
  %or = or i64 %shl, %shl3, !dbg !141
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !142
  %arrayidx4 = getelementptr inbounds i8, i8* %4, i64 2, !dbg !142
  %5 = load i8, i8* %arrayidx4, align 1, !dbg !142
  %conv5 = zext i8 %5 to i64, !dbg !143
  %shl6 = shl i64 %conv5, 40, !dbg !144
  %or7 = or i64 %or, %shl6, !dbg !145
  %6 = load i8*, i8** %buf.addr, align 8, !dbg !146
  %arrayidx8 = getelementptr inbounds i8, i8* %6, i64 3, !dbg !146
  %7 = load i8, i8* %arrayidx8, align 1, !dbg !146
  %conv9 = zext i8 %7 to i64, !dbg !147
  %shl10 = shl i64 %conv9, 32, !dbg !148
  %or11 = or i64 %or7, %shl10, !dbg !149
  %8 = load i8*, i8** %buf.addr, align 8, !dbg !150
  %arrayidx12 = getelementptr inbounds i8, i8* %8, i64 4, !dbg !150
  %9 = load i8, i8* %arrayidx12, align 1, !dbg !150
  %conv13 = zext i8 %9 to i64, !dbg !151
  %shl14 = shl i64 %conv13, 24, !dbg !152
  %or15 = or i64 %or11, %shl14, !dbg !153
  %10 = load i8*, i8** %buf.addr, align 8, !dbg !154
  %arrayidx16 = getelementptr inbounds i8, i8* %10, i64 5, !dbg !154
  %11 = load i8, i8* %arrayidx16, align 1, !dbg !154
  %conv17 = zext i8 %11 to i64, !dbg !155
  %shl18 = shl i64 %conv17, 16, !dbg !156
  %or19 = or i64 %or15, %shl18, !dbg !157
  %12 = load i8*, i8** %buf.addr, align 8, !dbg !158
  %arrayidx20 = getelementptr inbounds i8, i8* %12, i64 6, !dbg !158
  %13 = load i8, i8* %arrayidx20, align 1, !dbg !158
  %conv21 = zext i8 %13 to i64, !dbg !159
  %shl22 = shl i64 %conv21, 8, !dbg !160
  %or23 = or i64 %or19, %shl22, !dbg !161
  %14 = load i8*, i8** %buf.addr, align 8, !dbg !162
  %arrayidx24 = getelementptr inbounds i8, i8* %14, i64 7, !dbg !162
  %15 = load i8, i8* %arrayidx24, align 1, !dbg !162
  %conv25 = zext i8 %15 to i64, !dbg !163
  %or26 = or i64 %or23, %conv25, !dbg !164
  ret i64 %or26, !dbg !165
}

; Function Attrs: nounwind uwtable
define void @Curl_write16_le(i16 signext %value, i8* %buffer) #0 !dbg !25 {
entry:
  %value.addr = alloca i16, align 2
  %buffer.addr = alloca i8*, align 8
  store i16 %value, i16* %value.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %value.addr, metadata !166, metadata !44), !dbg !167
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !168, metadata !44), !dbg !169
  %0 = load i16, i16* %value.addr, align 2, !dbg !170
  %conv = sext i16 %0 to i32, !dbg !170
  %and = and i32 %conv, 255, !dbg !171
  %conv1 = trunc i32 %and to i8, !dbg !172
  %1 = load i8*, i8** %buffer.addr, align 8, !dbg !173
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !173
  store i8 %conv1, i8* %arrayidx, align 1, !dbg !174
  %2 = load i16, i16* %value.addr, align 2, !dbg !175
  %conv2 = sext i16 %2 to i32, !dbg !175
  %and3 = and i32 %conv2, 65280, !dbg !176
  %shr = ashr i32 %and3, 8, !dbg !177
  %conv4 = trunc i32 %shr to i8, !dbg !178
  %3 = load i8*, i8** %buffer.addr, align 8, !dbg !179
  %arrayidx5 = getelementptr inbounds i8, i8* %3, i64 1, !dbg !179
  store i8 %conv4, i8* %arrayidx5, align 1, !dbg !180
  ret void, !dbg !181
}

; Function Attrs: nounwind uwtable
define void @Curl_write32_le(i32 %value, i8* %buffer) #0 !dbg !31 {
entry:
  %value.addr = alloca i32, align 4
  %buffer.addr = alloca i8*, align 8
  store i32 %value, i32* %value.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %value.addr, metadata !182, metadata !44), !dbg !183
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !184, metadata !44), !dbg !185
  %0 = load i32, i32* %value.addr, align 4, !dbg !186
  %and = and i32 %0, 255, !dbg !187
  %conv = trunc i32 %and to i8, !dbg !188
  %1 = load i8*, i8** %buffer.addr, align 8, !dbg !189
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !189
  store i8 %conv, i8* %arrayidx, align 1, !dbg !190
  %2 = load i32, i32* %value.addr, align 4, !dbg !191
  %and1 = and i32 %2, 65280, !dbg !192
  %shr = ashr i32 %and1, 8, !dbg !193
  %conv2 = trunc i32 %shr to i8, !dbg !194
  %3 = load i8*, i8** %buffer.addr, align 8, !dbg !195
  %arrayidx3 = getelementptr inbounds i8, i8* %3, i64 1, !dbg !195
  store i8 %conv2, i8* %arrayidx3, align 1, !dbg !196
  %4 = load i32, i32* %value.addr, align 4, !dbg !197
  %and4 = and i32 %4, 16711680, !dbg !198
  %shr5 = ashr i32 %and4, 16, !dbg !199
  %conv6 = trunc i32 %shr5 to i8, !dbg !200
  %5 = load i8*, i8** %buffer.addr, align 8, !dbg !201
  %arrayidx7 = getelementptr inbounds i8, i8* %5, i64 2, !dbg !201
  store i8 %conv6, i8* %arrayidx7, align 1, !dbg !202
  %6 = load i32, i32* %value.addr, align 4, !dbg !203
  %and8 = and i32 %6, -16777216, !dbg !204
  %shr9 = lshr i32 %and8, 24, !dbg !205
  %conv10 = trunc i32 %shr9 to i8, !dbg !206
  %7 = load i8*, i8** %buffer.addr, align 8, !dbg !207
  %arrayidx11 = getelementptr inbounds i8, i8* %7, i64 3, !dbg !207
  store i8 %conv10, i8* %arrayidx11, align 1, !dbg !208
  ret void, !dbg !209
}

; Function Attrs: nounwind uwtable
define void @Curl_write64_le(i64 %value, i8* %buffer) #0 !dbg !35 {
entry:
  %value.addr = alloca i64, align 8
  %buffer.addr = alloca i8*, align 8
  store i64 %value, i64* %value.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %value.addr, metadata !210, metadata !44), !dbg !211
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !212, metadata !44), !dbg !213
  %0 = load i64, i64* %value.addr, align 8, !dbg !214
  %conv = trunc i64 %0 to i32, !dbg !215
  %1 = load i8*, i8** %buffer.addr, align 8, !dbg !216
  call void @Curl_write32_le(i32 %conv, i8* %1), !dbg !217
  %2 = load i64, i64* %value.addr, align 8, !dbg !218
  %shr = ashr i64 %2, 32, !dbg !219
  %conv1 = trunc i64 %shr to i32, !dbg !220
  %3 = load i8*, i8** %buffer.addr, align 8, !dbg !221
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 4, !dbg !222
  call void @Curl_write32_le(i32 %conv1, i8* %add.ptr), !dbg !223
  ret void, !dbg !224
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!40, !41}
!llvm.ident = !{!42}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !9)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_endian.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !5, !6, !7, !8}
!4 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!5 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!6 = !DIBasicType(name: "long long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!7 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!8 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!9 = !{!10, !16, !19, !22, !23, !24, !25, !31, !35}
!10 = distinct !DISubprogram(name: "Curl_read16_le", scope: !1, file: !1, line: 40, type: !11, isLocal: false, isDefinition: true, scopeLine: 41, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!11 = !DISubroutineType(types: !12)
!12 = !{!4, !13}
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64, align: 64)
!14 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !15)
!15 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!16 = distinct !DISubprogram(name: "Curl_read32_le", scope: !1, file: !1, line: 59, type: !17, isLocal: false, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{!5, !13}
!19 = distinct !DISubprogram(name: "Curl_read64_le", scope: !1, file: !1, line: 80, type: !20, isLocal: false, isDefinition: true, scopeLine: 81, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{!6, !13}
!22 = distinct !DISubprogram(name: "Curl_read16_be", scope: !1, file: !1, line: 116, type: !11, isLocal: false, isDefinition: true, scopeLine: 117, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!23 = distinct !DISubprogram(name: "Curl_read32_be", scope: !1, file: !1, line: 135, type: !17, isLocal: false, isDefinition: true, scopeLine: 136, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!24 = distinct !DISubprogram(name: "Curl_read64_be", scope: !1, file: !1, line: 156, type: !20, isLocal: false, isDefinition: true, scopeLine: 157, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!25 = distinct !DISubprogram(name: "Curl_write16_le", scope: !1, file: !1, line: 190, type: !26, isLocal: false, isDefinition: true, scopeLine: 191, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!26 = !DISubroutineType(types: !27)
!27 = !{null, !28, !30}
!28 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !29)
!29 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!31 = distinct !DISubprogram(name: "Curl_write32_le", scope: !1, file: !1, line: 207, type: !32, isLocal: false, isDefinition: true, scopeLine: 208, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!32 = !DISubroutineType(types: !33)
!33 = !{null, !34, !30}
!34 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !8)
!35 = distinct !DISubprogram(name: "Curl_write64_le", scope: !1, file: !1, line: 228, type: !36, isLocal: false, isDefinition: true, scopeLine: 232, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!36 = !DISubroutineType(types: !37)
!37 = !{null, !38, !30}
!38 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !39)
!39 = !DIBasicType(name: "long long int", size: 64, align: 64, encoding: DW_ATE_signed)
!40 = !{i32 2, !"Dwarf Version", i32 4}
!41 = !{i32 2, !"Debug Info Version", i32 3}
!42 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!43 = !DILocalVariable(name: "buf", arg: 1, scope: !10, file: !1, line: 40, type: !13)
!44 = !DIExpression()
!45 = !DILocation(line: 40, column: 52, scope: !10)
!46 = !DILocation(line: 42, column: 44, scope: !10)
!47 = !DILocation(line: 42, column: 28, scope: !10)
!48 = !DILocation(line: 42, column: 27, scope: !10)
!49 = !DILocation(line: 43, column: 44, scope: !10)
!50 = !DILocation(line: 43, column: 28, scope: !10)
!51 = !DILocation(line: 43, column: 51, scope: !10)
!52 = !DILocation(line: 42, column: 52, scope: !10)
!53 = !DILocation(line: 42, column: 10, scope: !10)
!54 = !DILocation(line: 42, column: 3, scope: !10)
!55 = !DILocalVariable(name: "buf", arg: 1, scope: !16, file: !1, line: 59, type: !13)
!56 = !DILocation(line: 59, column: 50, scope: !16)
!57 = !DILocation(line: 61, column: 25, scope: !16)
!58 = !DILocation(line: 61, column: 11, scope: !16)
!59 = !DILocation(line: 61, column: 50, scope: !16)
!60 = !DILocation(line: 61, column: 36, scope: !16)
!61 = !DILocation(line: 61, column: 57, scope: !16)
!62 = !DILocation(line: 61, column: 33, scope: !16)
!63 = !DILocation(line: 62, column: 25, scope: !16)
!64 = !DILocation(line: 62, column: 11, scope: !16)
!65 = !DILocation(line: 62, column: 32, scope: !16)
!66 = !DILocation(line: 61, column: 63, scope: !16)
!67 = !DILocation(line: 62, column: 56, scope: !16)
!68 = !DILocation(line: 62, column: 42, scope: !16)
!69 = !DILocation(line: 62, column: 63, scope: !16)
!70 = !DILocation(line: 62, column: 39, scope: !16)
!71 = !DILocation(line: 61, column: 3, scope: !16)
!72 = !DILocalVariable(name: "buf", arg: 1, scope: !19, file: !1, line: 80, type: !13)
!73 = !DILocation(line: 80, column: 56, scope: !19)
!74 = !DILocation(line: 82, column: 31, scope: !19)
!75 = !DILocation(line: 82, column: 11, scope: !19)
!76 = !DILocation(line: 83, column: 31, scope: !19)
!77 = !DILocation(line: 83, column: 11, scope: !19)
!78 = !DILocation(line: 83, column: 38, scope: !19)
!79 = !DILocation(line: 82, column: 39, scope: !19)
!80 = !DILocation(line: 84, column: 31, scope: !19)
!81 = !DILocation(line: 84, column: 11, scope: !19)
!82 = !DILocation(line: 84, column: 38, scope: !19)
!83 = !DILocation(line: 83, column: 44, scope: !19)
!84 = !DILocation(line: 85, column: 31, scope: !19)
!85 = !DILocation(line: 85, column: 11, scope: !19)
!86 = !DILocation(line: 85, column: 38, scope: !19)
!87 = !DILocation(line: 84, column: 45, scope: !19)
!88 = !DILocation(line: 86, column: 31, scope: !19)
!89 = !DILocation(line: 86, column: 11, scope: !19)
!90 = !DILocation(line: 86, column: 38, scope: !19)
!91 = !DILocation(line: 85, column: 45, scope: !19)
!92 = !DILocation(line: 87, column: 31, scope: !19)
!93 = !DILocation(line: 87, column: 11, scope: !19)
!94 = !DILocation(line: 87, column: 38, scope: !19)
!95 = !DILocation(line: 86, column: 45, scope: !19)
!96 = !DILocation(line: 88, column: 31, scope: !19)
!97 = !DILocation(line: 88, column: 11, scope: !19)
!98 = !DILocation(line: 88, column: 38, scope: !19)
!99 = !DILocation(line: 87, column: 45, scope: !19)
!100 = !DILocation(line: 89, column: 31, scope: !19)
!101 = !DILocation(line: 89, column: 11, scope: !19)
!102 = !DILocation(line: 89, column: 38, scope: !19)
!103 = !DILocation(line: 88, column: 45, scope: !19)
!104 = !DILocation(line: 82, column: 3, scope: !19)
!105 = !DILocalVariable(name: "buf", arg: 1, scope: !22, file: !1, line: 116, type: !13)
!106 = !DILocation(line: 116, column: 52, scope: !22)
!107 = !DILocation(line: 118, column: 44, scope: !22)
!108 = !DILocation(line: 118, column: 28, scope: !22)
!109 = !DILocation(line: 118, column: 51, scope: !22)
!110 = !DILocation(line: 119, column: 44, scope: !22)
!111 = !DILocation(line: 119, column: 28, scope: !22)
!112 = !DILocation(line: 119, column: 27, scope: !22)
!113 = !DILocation(line: 118, column: 57, scope: !22)
!114 = !DILocation(line: 118, column: 10, scope: !22)
!115 = !DILocation(line: 118, column: 3, scope: !22)
!116 = !DILocalVariable(name: "buf", arg: 1, scope: !23, file: !1, line: 135, type: !13)
!117 = !DILocation(line: 135, column: 50, scope: !23)
!118 = !DILocation(line: 137, column: 25, scope: !23)
!119 = !DILocation(line: 137, column: 11, scope: !23)
!120 = !DILocation(line: 137, column: 32, scope: !23)
!121 = !DILocation(line: 137, column: 56, scope: !23)
!122 = !DILocation(line: 137, column: 42, scope: !23)
!123 = !DILocation(line: 137, column: 63, scope: !23)
!124 = !DILocation(line: 137, column: 39, scope: !23)
!125 = !DILocation(line: 138, column: 25, scope: !23)
!126 = !DILocation(line: 138, column: 11, scope: !23)
!127 = !DILocation(line: 138, column: 32, scope: !23)
!128 = !DILocation(line: 137, column: 70, scope: !23)
!129 = !DILocation(line: 138, column: 55, scope: !23)
!130 = !DILocation(line: 138, column: 41, scope: !23)
!131 = !DILocation(line: 138, column: 38, scope: !23)
!132 = !DILocation(line: 137, column: 3, scope: !23)
!133 = !DILocalVariable(name: "buf", arg: 1, scope: !24, file: !1, line: 156, type: !13)
!134 = !DILocation(line: 156, column: 56, scope: !24)
!135 = !DILocation(line: 158, column: 31, scope: !24)
!136 = !DILocation(line: 158, column: 11, scope: !24)
!137 = !DILocation(line: 158, column: 38, scope: !24)
!138 = !DILocation(line: 159, column: 31, scope: !24)
!139 = !DILocation(line: 159, column: 11, scope: !24)
!140 = !DILocation(line: 159, column: 38, scope: !24)
!141 = !DILocation(line: 158, column: 45, scope: !24)
!142 = !DILocation(line: 160, column: 31, scope: !24)
!143 = !DILocation(line: 160, column: 11, scope: !24)
!144 = !DILocation(line: 160, column: 38, scope: !24)
!145 = !DILocation(line: 159, column: 45, scope: !24)
!146 = !DILocation(line: 161, column: 31, scope: !24)
!147 = !DILocation(line: 161, column: 11, scope: !24)
!148 = !DILocation(line: 161, column: 38, scope: !24)
!149 = !DILocation(line: 160, column: 45, scope: !24)
!150 = !DILocation(line: 162, column: 31, scope: !24)
!151 = !DILocation(line: 162, column: 11, scope: !24)
!152 = !DILocation(line: 162, column: 38, scope: !24)
!153 = !DILocation(line: 161, column: 45, scope: !24)
!154 = !DILocation(line: 163, column: 31, scope: !24)
!155 = !DILocation(line: 163, column: 11, scope: !24)
!156 = !DILocation(line: 163, column: 38, scope: !24)
!157 = !DILocation(line: 162, column: 45, scope: !24)
!158 = !DILocation(line: 164, column: 31, scope: !24)
!159 = !DILocation(line: 164, column: 11, scope: !24)
!160 = !DILocation(line: 164, column: 38, scope: !24)
!161 = !DILocation(line: 163, column: 45, scope: !24)
!162 = !DILocation(line: 165, column: 31, scope: !24)
!163 = !DILocation(line: 165, column: 11, scope: !24)
!164 = !DILocation(line: 164, column: 44, scope: !24)
!165 = !DILocation(line: 158, column: 3, scope: !24)
!166 = !DILocalVariable(name: "value", arg: 1, scope: !25, file: !1, line: 190, type: !28)
!167 = !DILocation(line: 190, column: 34, scope: !25)
!168 = !DILocalVariable(name: "buffer", arg: 2, scope: !25, file: !1, line: 190, type: !30)
!169 = !DILocation(line: 190, column: 56, scope: !25)
!170 = !DILocation(line: 192, column: 22, scope: !25)
!171 = !DILocation(line: 192, column: 28, scope: !25)
!172 = !DILocation(line: 192, column: 15, scope: !25)
!173 = !DILocation(line: 192, column: 3, scope: !25)
!174 = !DILocation(line: 192, column: 13, scope: !25)
!175 = !DILocation(line: 193, column: 23, scope: !25)
!176 = !DILocation(line: 193, column: 29, scope: !25)
!177 = !DILocation(line: 193, column: 39, scope: !25)
!178 = !DILocation(line: 193, column: 15, scope: !25)
!179 = !DILocation(line: 193, column: 3, scope: !25)
!180 = !DILocation(line: 193, column: 13, scope: !25)
!181 = !DILocation(line: 194, column: 1, scope: !25)
!182 = !DILocalVariable(name: "value", arg: 1, scope: !31, file: !1, line: 207, type: !34)
!183 = !DILocation(line: 207, column: 32, scope: !31)
!184 = !DILocalVariable(name: "buffer", arg: 2, scope: !31, file: !1, line: 207, type: !30)
!185 = !DILocation(line: 207, column: 54, scope: !31)
!186 = !DILocation(line: 209, column: 22, scope: !31)
!187 = !DILocation(line: 209, column: 28, scope: !31)
!188 = !DILocation(line: 209, column: 15, scope: !31)
!189 = !DILocation(line: 209, column: 3, scope: !31)
!190 = !DILocation(line: 209, column: 13, scope: !31)
!191 = !DILocation(line: 210, column: 23, scope: !31)
!192 = !DILocation(line: 210, column: 29, scope: !31)
!193 = !DILocation(line: 210, column: 43, scope: !31)
!194 = !DILocation(line: 210, column: 15, scope: !31)
!195 = !DILocation(line: 210, column: 3, scope: !31)
!196 = !DILocation(line: 210, column: 13, scope: !31)
!197 = !DILocation(line: 211, column: 23, scope: !31)
!198 = !DILocation(line: 211, column: 29, scope: !31)
!199 = !DILocation(line: 211, column: 43, scope: !31)
!200 = !DILocation(line: 211, column: 15, scope: !31)
!201 = !DILocation(line: 211, column: 3, scope: !31)
!202 = !DILocation(line: 211, column: 13, scope: !31)
!203 = !DILocation(line: 212, column: 23, scope: !31)
!204 = !DILocation(line: 212, column: 29, scope: !31)
!205 = !DILocation(line: 212, column: 43, scope: !31)
!206 = !DILocation(line: 212, column: 15, scope: !31)
!207 = !DILocation(line: 212, column: 3, scope: !31)
!208 = !DILocation(line: 212, column: 13, scope: !31)
!209 = !DILocation(line: 213, column: 1, scope: !31)
!210 = !DILocalVariable(name: "value", arg: 1, scope: !35, file: !1, line: 228, type: !38)
!211 = !DILocation(line: 228, column: 38, scope: !35)
!212 = !DILocalVariable(name: "buffer", arg: 2, scope: !35, file: !1, line: 228, type: !30)
!213 = !DILocation(line: 228, column: 60, scope: !35)
!214 = !DILocation(line: 233, column: 24, scope: !35)
!215 = !DILocation(line: 233, column: 19, scope: !35)
!216 = !DILocation(line: 233, column: 31, scope: !35)
!217 = !DILocation(line: 233, column: 3, scope: !35)
!218 = !DILocation(line: 234, column: 25, scope: !35)
!219 = !DILocation(line: 234, column: 31, scope: !35)
!220 = !DILocation(line: 234, column: 19, scope: !35)
!221 = !DILocation(line: 234, column: 39, scope: !35)
!222 = !DILocation(line: 234, column: 46, scope: !35)
!223 = !DILocation(line: 234, column: 3, scope: !35)
!224 = !DILocation(line: 235, column: 1, scope: !35)
